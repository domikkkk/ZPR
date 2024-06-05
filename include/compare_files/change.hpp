// Author: Fedir Tsupin
#ifndef CHANGE_HPP
#define CHANGE_HPP
#pragma once

#include <string>


enum class ChangeType {
    Addition,
    Deletion,
    Shift
};

class Change {
private:
    ChangeType type;
    size_t position;
    std::string text;
public:
    Change(ChangeType type, int position, std::string text) :
        type(type), position(position), text(text) {};
    ChangeType getType() const;
    size_t getPosition() const;
    std::string getText() const;

    bool operator==(const Change& other) const;
};


#endif