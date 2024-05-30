#include <compare_files/file.hpp>


File::File(fs::path path): path(path) {
    this->read();
}


Block &File::operator[](const size_t &i) {
    return this->blocks[i];
}


void File::read() {
    std::ifstream fileStream(this->path);
    if (fs::exists(this->path)) {
        if (fileStream.is_open()) {
            text.assign((std::istreambuf_iterator<char>(fileStream)),
                        (std::istreambuf_iterator<char>()));
            fileStream.close();
        }
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
}


const std::string &File::getText() {
    return this->text;
}


void File::split(const std::string delimiter) {
    std::size_t pos = 0;
    std::size_t found;

    while ((found = text.find(delimiter, pos)) != std::string::npos) {
        this->blocks.push_back(Block(text.substr(pos, found - pos), pos, found));
        pos = found + delimiter.size();
    }
    
    this->blocks.push_back(Block(text.substr(pos), pos, text.size()));
}
