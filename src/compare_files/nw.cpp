#include <compare_files/nw.hpp>


int NeedlemanWunsch::getAlignmentScore() const {
    return alignmentScore;
}


Matrix NeedlemanWunsch::createMatrix(int rows, int cols) {
    Matrix matrix(new std::unique_ptr<int[]>[rows]);
    for (int i = 0; i < rows; ++i) {
        matrix[i].reset(new int[cols]);
    }
    return matrix;
}


std::pair<std::vector<std::string>, std::vector<std::string>> NeedlemanWunsch::reconstructAlignment(const std::vector<std::string>& s1, const std::vector<std::string>& s2, const Matrix& dp) {
    std::vector<std::string> aligneds1, aligneds2;
    int i = s1.size(), j = s2.size();
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? matchScore : mismatchScore)) {
            aligneds1.push_back(s1[i - 1]);
            aligneds2.push_back(s2[j - 1]);
            --i;
            --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + gapPenalty) {
            aligneds1.push_back(s1[i - 1]);
            aligneds2.push_back("");
            --i;
        } else {
            aligneds1.push_back("");
            aligneds2.push_back(s2[j - 1]);
            --j;
        }
    }
    return std::make_pair(aligneds1, aligneds2);
}

int NeedlemanWunsch::computeMatchValue(const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
    int m = s1.size();
    int n = s2.size();
    auto dp = createMatrix(m + 1, n + 1);

    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i * gapPenalty;
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j * gapPenalty;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int match = dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? matchScore : mismatchScore);
            int deleteGap = dp[i - 1][j] + gapPenalty;
            int insertGap = dp[i][j - 1] + gapPenalty;
            dp[i][j] = std::max({match, deleteGap, insertGap});
        }
    }
    this->alignments = reconstructAlignment(s1, s2, dp);
    this->alignmentScore = dp[m][n];

    return alignmentScore;
}