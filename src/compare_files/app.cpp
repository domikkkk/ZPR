#include <compare_files/app.hpp>


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
                similarBlocks.push_back(std::make_pair(Block("", -1, -1), f2.getBlocks()[i]));
            else
                similarBlocks.push_back(std::make_pair(f1.getBlocks()[i], Block("", -1, -1)));
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
    // Sort matches by normalized match value
    std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) {
        float a_val = std::get<2>(a);
        float b_val = std::get<2>(b);

        // Handle NaN values
        if (std::isnan(a_val)) {
            return false; // Move NaNs to the end
        } else if (std::isnan(b_val)) {
            return true; // Move NaNs to the end
        }

        return a_val > b_val; // Normal comparison
    });
    for (auto [b1, b2, score] : matches) {
        std::cout << "[" + b1.getText() + "] ";
        std::cout << "[" + b2.getText() + "] ";
        std::cout << score << std::endl;
    }
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


//helper function for debugging
void printBlocks(File& f1, File&f2) {
    std::cout << "f1 blocks:" << std::endl;
    for (auto block : f1.getBlocks()) {
        std:: cout << "[" + block.getText() + "]" << std::endl;
    }
    std::cout << "f2 blocks:" << std::endl;
    for (auto block : f2.getBlocks()) {
        std:: cout << "[" + block.getText() + "]" << std::endl;
    }
}


std::vector<TextDiff> App::findChanges(std::vector<std::pair<Block, Block>> similarBlocks) const {
    std::vector<TextDiff> changes = {};
    Comparator comp = Comparator();
    for (auto [original, modified] : similarBlocks) {
        auto changesInBlocks = comp.detectChanges(original.getText(), modified.getText(), original.getStartPos(), modified.getStartPos());
        changes.push_back(TextDiff(original, modified, changesInBlocks));
    }
    return changes;
}


std::vector<TextDiff> App::compare() {
    // 1. Split files into blocks
    // 2. Find similar blocks with NW
    // 3. Find differences in blocks with Comparator
    // 4. Return differences
    this->counter = 0;
    printBlocks(f1, f2);
    auto similarBlocks = findSimilarBlocks();
    auto changes = findChanges(similarBlocks);
    return changes;
}


void App::setFiles(const File &f1, const File &f2) {
    this->f1 = f1;
    this->f2 = f2;
}


void App::calculateMaxCount() {
    this->maxCount = f1.get_size() + f2.get_size();
}
