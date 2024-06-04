#ifndef APP_HPP
#define APP_HPP
#pragma once

#include <compare_files/file.hpp>
#include <compare_files/textdiff.hpp>
#include <compare_files/nw.hpp>
#include <compare_files/comparator.hpp>
#include <vector>
#include <cmath>


class App {
private:
    File f1, f2;
public:
    App() = default;
    App(const File &f1, const File &f2) : f1(f1), f2(f2) {};
    void compare();
    std::vector<std::pair<Block, Block>> findSimilarBlocks();
    std::vector<TextDiff> getChanges() const;
    void findChanges(std::vector<std::pair<Block, Block>> similarBlocks);
    void setFiles(const File &f1, const File &f2);
    void calculateMaxCount();
    int counter = 0;
    int maxCount = 0;
private:
    int findBlockIdx(const std::vector<Block>& blocks, Block& block) const;
    void addUnpairedBlocks(std::vector<bool> const& isMatched, std::vector<std::pair<Block, Block>>& similarBlocks, bool wasAdded) const;
    std::vector<TextDiff> changes = {};
};

#endif