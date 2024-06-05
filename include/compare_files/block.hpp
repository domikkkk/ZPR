#ifndef TEXT_HPP
#define TEXT_HPP
#pragma once
#include <string>
#include <iostream>


class Block {
public:
    Block(std::string text, int startPos, int endPos, int newLinesBefore)
        : text(text), startPos(startPos), endPos(endPos), newLinesBefore(newLinesBefore) {};
    std::string getText() const;
    int getStartPos() const;
    int getEndPos() const;
    int getNewLinesBefore() const;

    bool operator==(const Block& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Block& text);
protected:
    std::string text;
    int startPos;
    int endPos;
    int newLinesBefore;
};

#endif
