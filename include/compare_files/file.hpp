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
    File(fs::path path) : path(path) {};
    std::string read();
    std::string write(std::string text);
    std::vector<Block> split(const std::string delimiter) const;
protected:
    fs::path path;
    std::string text;  // all text
    std::vector<Block> blocks;  // blocks of texts
};

#endif
