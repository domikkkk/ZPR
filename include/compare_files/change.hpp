#ifndef CHANGE_HPP
#define CHANGE_HPP
#pragma once

enum class ChangeType {
    Addition,
    Deletion
};

class Change {
private:
    ChangeType type;
    int position;
    std::string text;
public:
    Change(ChangeType type, int position, std::string text) :
        type(type), position(position), text(text) {};
    ChangeType getType() const;
    int getPosition() const;
    std::string getText() const;
};


#endif