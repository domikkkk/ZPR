#include <compare_files/file.hpp>


File::File(const fs::path &path): path(path) {
}


Block &File::operator[](const std::size_t &i) {
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


std::size_t countCharacters(const std::string& filename) {
    std::wifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return 0;
    }
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::wstring content;
    wchar_t ch;
    while (file.get(ch)) {
        content.push_back(ch);
    }

    return content.size();
}


void File::splitByParagraphs() {
    std::size_t pos = 0;
    std::size_t found;
    this->splited = true;
    const std::string delimiter = "\n\n";

    std::size_t totalChars = countCharacters(path.string());

    while ((found = text.find(delimiter, pos)) != std::string::npos) {
        std::size_t start = pos;
        std::size_t length = found - pos;
        this->blocks.push_back(Block(text.substr(start, length), start, found));

        pos = found + delimiter.size();
        while (text[pos] == '\n') {
            pos++;
        }
    }
    if (pos < text.size()) {
        std::size_t start = pos;
        this->blocks.push_back(Block(text.substr(start), start, totalChars));
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
