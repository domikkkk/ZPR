// Author: Fedir Tsupin
#include <compare_files/block.hpp>


std::string Block::getText() const {
    return text;
}


int Block::getStartPos() const {
    return startPos;
}


int Block::getEndPos() const {
    return endPos;
}


int Block::getNewLinesBefore() const {
    return newLinesBefore;
}

bool Block::operator==(const Block& other) const {
    return (other.getText() == text && other.getStartPos() == startPos && other.getEndPos() == endPos);
}
