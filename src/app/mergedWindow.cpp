#include <mergedWindow.hpp>


MergedWindow::MergedWindow(QWidget *parent): QMainWindow(parent) {
    this->setWindowTitle("Merged Text");
    this->resize(800, 600);
}


void MergedWindow::addTWidget(TWidget *twidget) {
    delete this->centralWidget();
    this->setCentralWidget(twidget);
}