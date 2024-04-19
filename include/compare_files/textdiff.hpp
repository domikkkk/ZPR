#ifndef TEXTDIFF_HPP
#define TEXTDIFF_HPP
#pragma once
#include <compare_files/block.hpp>


class TextDiff {
public:
    TextDiff(Block original, Block old) : original(original), old(old) {}
    Block getOriginal() const;
    Block getOld() const;
protected:
    Block original;
    Block old;
};

#endif
