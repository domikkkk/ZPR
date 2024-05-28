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
