// Author: Fedir Tsupin
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
    float alignmentScore;
public:
    float computeMatchValue(const std::vector<std::string>& s1, const std::vector<std::string>& s2);
    NeedlemanWunsch(int matchScore=1, int mismatchScore=-1, int gapPenalty=-1)
        : matchScore(matchScore), mismatchScore(mismatchScore), gapPenalty(gapPenalty), alignmentScore(0) {};
    float getAlignmentScore() const;
private:
    Matrix createMatrix(int rows, int cols);
    void deleteMatrix(int** matrix, int rows);
};

#endif