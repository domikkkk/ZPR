#include <mainwindow.hpp>
#include <CompareFiles>
#include <filesystem>
#include <QApplication>
#include <QtWidgets>

int main(int argc, char **argv) {
    Block("Test", 1, 5);
    QApplication a(argc, argv);
    QWidget w;
    w.show();
    return a.exec();
}
