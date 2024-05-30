#ifndef FILE_HPP
#define FILE_HPP
#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <compare_files/block.hpp>

namespace fs = std::filesystem;

class File {
public:
    File() = default;
    explicit File(const fs::path &path);
    void read();
    const std::string &getText();
    std::string get_filename();
    std::string write(std::string text);
    void split(const std::string delimiter);
    Block &operator[](const size_t &i);
protected:
    fs::path path;
    std::string text;  // all text
    std::vector<Block> blocks;  // blocks of texts
};


#endif
