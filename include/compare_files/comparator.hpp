// Author: Fedir Tsupin
#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <compare_files/change.hpp>
#include <compare_files/file.hpp>


class Comparator {
public:
    std::vector<Change> detectChanges(const std::string& text1, const std::string& text2, int startPos1, int startPos2, int newLinesBefore1, int newLinesBefore2) const;
    std::vector<std::string> splitIntoTokens(const std::string& text) const;
};

#endif