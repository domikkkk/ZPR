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
    std::vector<Block> getBlocks() const;

    void read();
    void save() const;
    void write(const std::string &text);
    void split(const std::string &delimiter);
    void splitByParagraphs();
    void change_filename(const fs::path &new_path);
    bool was_read() const;
    int get_size() const;
    bool wasSplited() const;

    Block &operator[](const std::size_t &i);
protected:
    bool m_read = false;
    bool splited = false;
    fs::path path;
    std::string text;  // all text
    std::vector<Block> blocks;  // blocks of texts
};

std::size_t countCharacters(const std::string& filename);

#endif
