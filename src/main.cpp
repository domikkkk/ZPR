#include <mainwindow.hpp>
#include <compare_files/kmp.hpp>
#include <QApplication>
#include <QtWidgets>


int main(int argc, char **argv) {
    QApplication a(argc, argv);
    QWidget w;
    w.show();
    return a.exec();
}
