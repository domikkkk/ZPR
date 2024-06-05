// Author: Dominik Sidorczuk

#ifndef KMP_HPP
#define KMP_HPP
#pragma once
#include <string>
#include <vector>


typedef struct {
    int len;
    std::string text;
} kmp;


int *computePreffixArray(const kmp &pattern);
void freeArray(int *arr);
std::vector<int> kmpSearch(const std::string &text, const std::string &pattern);


#endif
