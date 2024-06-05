// Author: Dominik Sidorczuk
#include <compare_files/kmp.hpp>


int *computePreffixArray(const kmp &pattern) {
    // length of the previous longest prefix suffix
    int *prefix_arr = new int[pattern.len];
    prefix_arr[0] = 0; // first is always 0
    int i = 0, j = 1;
    while (j < pattern.len) {
        if (pattern.text[j] == pattern.text[i]) {
            i++;
            prefix_arr[j] = i;
            j++;
        }
        else if (i != 0) {
            i = prefix_arr[i - 1];
        }
        else {
            prefix_arr[j++] = 0;
        }
    }
    return prefix_arr;
}


void freeArray(int *arr) {
    delete[] arr;
}


std::vector<int> kmpSearch(const std::string &text, const std::string &pattern) {
    std::vector<int> indices;
    int N = text.length();
    int M = pattern.length();
    int *prefix_arr = computePreffixArray({M, pattern});
    int i = 0, j = 0;
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == M) {
            indices.push_back(i - j);
            j = prefix_arr[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = prefix_arr[j - 1];
            } else {
                i++;
            }
        }
    }
    freeArray(prefix_arr);
    return indices;
}
