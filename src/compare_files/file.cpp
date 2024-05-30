#include <compare_files/file.hpp>


std::string File::read() {
    std::ifstream fileStream(path);
    if (fs::exists(path)) {
        if (fileStream.is_open()) {
            text.assign((std::istreambuf_iterator<char>(fileStream)),
                        (std::istreambuf_iterator<char>()));
            fileStream.close();
        }
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
    return text;
}

std::vector<Block> File::split(const std::string delimiter) const {
    std::vector<Block> blocks;
    std::size_t pos = 0;
    std::size_t found;

    while ((found = text.find(delimiter, pos)) != std::string::npos) {
        blocks.push_back(Block(text.substr(pos, found - pos), pos, found));
        pos = found + delimiter.size();
    }

    blocks.push_back(Block(text.substr(pos), pos, text.size()));
    return blocks;
}
