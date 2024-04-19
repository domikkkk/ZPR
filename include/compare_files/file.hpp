#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class File {
    fs::path path;
public:
    File(fs::path path) : path(path) {}
    std::string readRange(int start, int end) const;
    std::string write(std::string text);
};
#endif