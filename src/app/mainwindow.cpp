#include <mainwindow.hpp>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>


Point::Point(const int &x, const int &y) {
   this->x = x;
   this->y = y;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   this->gen_text("Welcome!", 24, true);
   this->setWindowTitle("Files compare");
   this->resize(800, 600);
}


MainWindow::~MainWindow() {

}


void MainWindow::gen_text(const QString &text, const int &size, const bool &if_bold) {
   QLabel *Label = new QLabel(text, this);
   Label->setAlignment(Qt::AlignHCenter);
   // Label->setGeometry(200, 100, 600, 100);

   QFont font = Label->font();
   font.setPointSize(size);
   font.setBold(if_bold);
   Label->setFont(font);
   
   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(Label);

   QWidget *widget = new QWidget(this);
   widget->setLayout(layout);

   this->setCentralWidget(widget);
}
