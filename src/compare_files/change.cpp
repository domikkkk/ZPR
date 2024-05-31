#include <compare_files/change.hpp>


ChangeType Change::getType() const {
    return type;
}


int Change::getPosition() const {
    return position;
}


std::string Change::getText() const {
    return text;
}
