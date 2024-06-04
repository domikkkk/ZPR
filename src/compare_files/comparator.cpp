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


std::wstring utf8_to_wstring(const std::string& utf8str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(utf8str);
}


std::vector<Change> Comparator::detectChanges(const std::string& text1, const std::string& text2, int startPos1, int startPos2) const {
    std::vector<std::string> tokens1 = splitIntoTokens(text1);
    std::vector<std::string> tokens2 = splitIntoTokens(text2);
    std::vector<Change> changes;

    size_t i = 0, j = 0;
    size_t position1 = startPos1;
    size_t position2 = startPos2;
    if (text1 == text2 && startPos1 != startPos2) {
        changes.push_back(Change(ChangeType::Shift, startPos1, text1));
    }
    else {
    while (i < tokens1.size() || j < tokens2.size()) {
        if (i < tokens1.size() && j < tokens2.size() && tokens1[i] == tokens2[j]) {
            ++i;
            ++j;
            auto wtoken1 = utf8_to_wstring(tokens1[i - 1]);
            auto wtoken2 = utf8_to_wstring(tokens2[j - 1]);
            position1 += wtoken1.size();
            position2 += wtoken2.size();
        } else {
            if (i < tokens1.size()) {
                changes.push_back(Change(ChangeType::Deletion, position1, tokens1[i]));
                position1 += utf8_to_wstring(tokens1[i]).size();
                ++i;
            }
            if (j < tokens2.size()) {
                changes.push_back(Change(ChangeType::Addition, position2, tokens2[j]));
                position2 += utf8_to_wstring(tokens2[j]).size();
                ++j;
            }
        }
    }
    }
    return changes;
}