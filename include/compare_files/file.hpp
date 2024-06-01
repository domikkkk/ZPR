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

    std::string getText() const;
    const fs::path &get_filename() const;

    void read();
    std::string write(std::string text);
    void split(const std::string &delimiter);
    void change_filename(const fs::path &new_path);
    bool was_read() const;

    Block &operator[](const size_t &i);
protected:
    bool m_read = false;
    fs::path path;
    std::string text;  // all text
    std::vector<Block> blocks;  // blocks of texts
};


#endif
