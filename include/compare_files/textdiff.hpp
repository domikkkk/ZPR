// Author: Fedir Tsupin
#ifndef TEXTDIFF_HPP
#define TEXTDIFF_HPP
#pragma once
#include <compare_files/block.hpp>
#include <compare_files/change.hpp>
#include <vector>

class TextDiff {
public:
    TextDiff(Block original, Block modified, std::vector<Change> changes) : original(original), modified(modified),  changes(changes) {}
    Block getOriginal() const;
    Block getModified() const;
    std::vector<Change> getChanges() const;
protected:
    Block original;
    Block modified;
    std::vector<Change> changes;
};

#endif
