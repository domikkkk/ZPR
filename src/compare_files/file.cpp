#include <compare_files/file.hpp>


File::File(const fs::path &path): path(path) {
    // this->read();  // może jednak nie czytajmy
}


Block &File::operator[](const size_t &i) {
    return this->blocks[i];
}


void File::read() {
    std::ifstream fileStream(this->path);
    this->blocks.clear();
    if (fs::exists(this->path)) {
        if (fileStream.is_open()) {
            text.assign((std::istreambuf_iterator<char>(fileStream)),
                        (std::istreambuf_iterator<char>()));
            fileStream.close();
        }
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
    this->m_read = true;
}


void File::write(const std::string &text) {
    this->text = text;
}


void File::save() const {
    std::ofstream fileStream(this->path);
    if (fileStream.is_open()) {
        fileStream << this->text;
        fileStream.close();
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}


void File::change_filename(const fs::path &new_path) {
    this->path = new_path;
    this->m_read = false;
    this->splited = false;
}


std::string File::getText() const {
    return this->text;
}


const fs::path &File::get_filename() const {
    return this->path;
}


std::vector<Block> File::getBlocks() const {
    return blocks;
}


void File::split(const std::string &delimiter) {
    std::size_t pos = 0;
    std::size_t found;

    while ((found = text.find(delimiter, pos)) != std::string::npos) {
        this->blocks.push_back(Block(text.substr(pos, found - pos), pos, found));
        pos = found + delimiter.size();
    }

    this->blocks.push_back(Block(text.substr(pos), pos, text.size()));
}


void File::splitByParagraphs() {
    std::size_t pos = 0;
    std::size_t found;
    this->splited = true;
    const std::string delimiter = "\n\n";

    while ((found = text.find(delimiter, pos)) != std::string::npos) {
        this->blocks.push_back(Block(text.substr(pos, found - pos), pos, found));
        pos = found + delimiter.size();
        while (text[pos] == '\r' && text[pos + 1] == '\n') {
            pos += 2;
        }
    }
    if (pos < text.size()) {
        this->blocks.push_back(Block(text.substr(pos), pos, text.size()));
    }
}


bool File::was_read() const {
    return this->m_read;
}


int File::get_size() const {
    return this->blocks.size();
}


bool File::wasSplited() const {
    return this->splited;
}
