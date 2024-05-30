#ifndef NW_HPP
#define NW_HPP
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <memory>

using Matrix = std::unique_ptr<std::unique_ptr<int[]>[]>;

class NeedlemanWunsch {
private:
    const int matchScore, mismatchScore, gapPenalty;
    int alignmentScore;
    std::pair<std::vector<std::string>, std::vector<std::string>> alignments;
public:
    int computeMatchValue(const std::vector<std::string>& s1, const std::vector<std::string>& s2);
    NeedlemanWunsch(int matchScore=1, int mismatchScore=-1, int gapPenalty=-2)
        : matchScore(matchScore), mismatchScore(mismatchScore), gapPenalty(gapPenalty), alignmentScore(0) {
            std::vector<std::string> a, b;
            alignments = std::make_pair(a, b);
        };
    int getAlignmentScore() const;
private:
    Matrix createMatrix(int rows, int cols);
    void deleteMatrix(int** matrix, int rows);
    std::pair<std::vector<std::string>, std::vector<std::string>> reconstructAlignment(const std::vector<std::string>& s1, const std::vector<std::string>& s2, const Matrix& dp);
};

#endif