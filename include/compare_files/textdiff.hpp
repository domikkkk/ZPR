#ifndef TEXTDIFF_HPP
#define TEXTDIFF_HPP

#include <text.hpp>

class TextDiff {
    Text original;
    Text old;
public:
    TextDiff(Text original, Text old) : original(original), old(old) {}
    Text getOriginal() const;
    Text getOld() const;
}
#endif
