#ifndef APP_HPP
#define APP_HPP
#pragma once

#include <compare_files/file.hpp>
#include <compare_files/textdiff.hpp>
#include <compare_files/nw.hpp>
#include <compare_files/comparator.hpp>
#include <vector>

class App {
private:
    File f1, f2;
public:
    App(File f1, File f2) : f1(f1), f2(f2) {};
    std::vector<TextDiff> compare();
    std::vector<std::pair<Block, Block>> findSimilarBlocks() const;
    std::vector<TextDiff> findChanges(std::vector<std::pair<Block, Block>> similarBlocks) const;
private:
    int findBlockIdx(const std::vector<Block>& blocks, Block& block) const;
    void addUnpairedBlocks(std::vector<bool> const& isMatched, std::vector<std::pair<Block, Block>>& similarBlocks, bool wasAdded) const;
};

#endif