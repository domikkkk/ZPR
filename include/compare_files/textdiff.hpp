#ifndef TEXTDIFF_HPP
#define TEXTDIFF_HPP
#pragma once
#include <compare_files/block.hpp>
#include <compare_files/change.hpp>
#include <vector>

class TextDiff {
public:
    TextDiff(Block original, Block old, std::vector<Change> changes) : original(original), old(old),  changes(changes) {}
    Block getOriginal() const;
    Block getOld() const;
protected:
    Block original;
    Block old;
    std::vector<Change> changes;
};

#endif
