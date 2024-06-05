#include <compare_files/app.hpp>
#include <algorithm>


int App::findBlockIdx(const std::vector<Block>& blocks, Block& block) const {
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i] == block)
            return i;
    }
    return -1;
}


void App::addUnpairedBlocks(std::vector<bool> const& isMatched, std::vector<std::pair<Block, Block>>& similarBlocks, bool wasAdded) const {
    for (size_t i = 0; i < isMatched.size(); ++i) {
        if (!isMatched[i]) {
            if (wasAdded)
                similarBlocks.push_back(std::make_pair(Block("", -1, -1, 0), f2.getBlocks()[i]));
            else
                similarBlocks.push_back(std::make_pair(f1.getBlocks()[i], Block("", -1, -1, 0)));
        }
    }
}


std::vector<std::pair<Block, Block>> App::findSimilarBlocks() {
    NeedlemanWunsch nw = NeedlemanWunsch();
    Comparator comp = Comparator();
    std::vector<std::tuple<Block, Block, float>> matches;
    // Iterate through all pairs of blocks from f1 and f2
    for (const Block& block1 : f1.getBlocks()) {
        for (const Block& block2 : f2.getBlocks()) {
            // Compute match value
            std::vector<std::string> tokens1 = comp.splitIntoTokens(block1.getText());
            std::vector<std::string> tokens2 = comp.splitIntoTokens(block2.getText());
            float matchValue = nw.computeMatchValue(tokens1, tokens2);
            // Store pair of blocks and match value
            matches.push_back(std::make_tuple(block1, block2, matchValue));
            ++this->counter;
        }
    }
    std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) {
        float a_val = std::get<2>(a);
        float b_val = std::get<2>(b);
        if (std::isnan(a_val)) {
            return false;
        } else if (std::isnan(b_val)) {
            return true;
        }

        return a_val > b_val;
    });
    std::vector<std::pair<Block, Block>> similarBlocks = {};
    std::vector<bool> f1BlockMatched(f1.getBlocks().size(), false);
    std::vector<bool> f2BlockMatched(f2.getBlocks().size(), false);
    // Convert sorted matches into vector of pairs of blocks
    for (auto blockPair : matches) {
        auto f1BlockIdx = findBlockIdx(f1.getBlocks(), std::get<0>(blockPair));
        auto f2BlockIdx = findBlockIdx(f2.getBlocks(), std::get<1>(blockPair));
        if (!f1BlockMatched[f1BlockIdx] && !f2BlockMatched[f2BlockIdx]) {
            similarBlocks.push_back(std::make_pair(std::get<0>(blockPair), std::get<1>(blockPair)));
            f1BlockMatched[f1BlockIdx] = true;
            f2BlockMatched[f2BlockIdx] = true;
        }
    }
    addUnpairedBlocks(f1BlockMatched, similarBlocks, false);
    addUnpairedBlocks(f2BlockMatched, similarBlocks, true);
    return similarBlocks;
}


void App::findChanges(std::vector<std::pair<Block, Block>> similarBlocks) {
    this->changes.clear();
    Comparator comp = Comparator();
    for (auto [original, modified] : similarBlocks) {
        auto changesInBlocks = comp.detectChanges(original.getText(), modified.getText(), original.getStartPos(), modified.getStartPos(), original.getNewLinesBefore(), modified.getNewLinesBefore());
        this->changes.push_back(TextDiff(original, modified, changesInBlocks));
    }
}


std::vector<TextDiff> App::getChanges() const {
    return this->changes;
}


void App::compare() {
    this->counter = 0;
    auto similarBlocks = findSimilarBlocks();
    this->findChanges(similarBlocks);
}


void App::setFiles(const File &f1, const File &f2) {
    this->f1 = f1;
    this->f2 = f2;
}


void App::calculateMaxCount() {
    this->maxCount = f1.get_size() + f2.get_size();
}
