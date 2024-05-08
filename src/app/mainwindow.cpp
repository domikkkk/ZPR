#include <mainwindow.hpp>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   QLabel *welcomeLabel = new QLabel("Welcome!", this);
   welcomeLabel->setAlignment(Qt::AlignHCenter);

   QFont font = welcomeLabel->font();
   font.setPointSize(24);
   font.setBold(true);
   welcomeLabel->setFont(font);
   
   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(welcomeLabel);

   QWidget *widget = new QWidget(this);
   widget->setLayout(layout);

   this->setCentralWidget(widget);
   this->setWindowTitle("Files compare");
   this->resize(800, 600);
}


MainWindow::~MainWindow() {

}
