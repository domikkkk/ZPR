// Author: Fedir Tsupin
#include <compare_files/change.hpp>


ChangeType Change::getType() const {
    return type;
}


size_t Change::getPosition() const {
    return position;
}


std::string Change::getText() const {
    return text;
}


bool Change::operator==(const Change& other) const {
    return (type == other.getType() && position == other.getPosition() && text == other.getText());
}
