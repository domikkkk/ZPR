#include <compare_files/comparator.hpp>


std::vector<std::string> Comparator::splitIntoTokens(const std::string& text) const {
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;
    bool inWhiteSpaceSequence = false;
    while (std::getline(iss, token, ' ')) {
        if (token.empty()) {
            if (!inWhiteSpaceSequence ) {
                if (!tokens.empty())
                    tokens.back() += " ";
                else
                    tokens.push_back(" ");
                inWhiteSpaceSequence = true;
            }
            else {
                tokens.back() += " ";
            }
        } else {
            tokens.push_back(token);
            if (!iss.eof()) {
               tokens.push_back(" ");
            }
            inWhiteSpaceSequence = false;
        }
    }
    return tokens;
}

std::vector<Change> Comparator::detectChanges(const std::string& text1, const std::string& text2) const {
    std::vector<std::string> tokens1 = splitIntoTokens(text1);
    std::vector<std::string> tokens2 = splitIntoTokens(text2);
    std::vector<Change> changes;

    size_t i = 0, j = 0;
    size_t position = 0;

    while (i < tokens1.size() || j < tokens2.size()) {
        if (i < tokens1.size() && j < tokens2.size() && tokens1[i] == tokens2[j]) {
            ++i;
            ++j;
            position += tokens1[i - 1].size();
        } else {
            if (i < tokens1.size()) {
                changes.push_back(Change(ChangeType::Deletion, position, tokens1[i]));
                ++i;
            }
            if (j < tokens2.size()) {
                changes.push_back(Change(ChangeType::Addition, position, tokens2[j]));
                ++j;
            }
            if (i < tokens1.size()) {
                position += tokens1[i].size();
            } else if (j < tokens2.size()) {
                position += tokens2[j].size();
            }
        }
    }
    return changes;
}