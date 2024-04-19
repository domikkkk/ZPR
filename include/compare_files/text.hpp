#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>
#include "file.hpp"
#include <iostream>

class Text {
    std::string text;
    int startPos;
    int endPos;
    File sourceFile;
public:
    Text(std::string text, int startPos, int endPos, File sourceFile)
        : text(text), startPos(startPos), endPos(endPos), sourceFile(sourceFile) {}
    std::string getText() const;
    int getStartPos() const;
    int getEndPos() const;
    File getSourceFile() const;

    bool operator==(const Text& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Text& text);
};
#endif
