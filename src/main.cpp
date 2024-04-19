#include <mainwindow.hpp>
#include <compare_files/kmp.hpp>
#include <compare_files/text.hpp>
#include <compare_files/file.hpp>
#include <filesystem>
#include <QApplication>
#include <QtWidgets>

int main(int argc, char **argv) {
    Text("Test", 1, 5, File(std::filesystem::path("/path")));
    QApplication a(argc, argv);
    QWidget w;
    w.show();
    return a.exec();
}
