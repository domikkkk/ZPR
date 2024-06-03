#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <compare_files/change.hpp>

class Comparator {
public:
    std::vector<Change> detectChanges(const std::string& text1, const std::string& text2) const;
    std::vector<std::string> splitIntoTokens(const std::string& text) const;
};

#endif