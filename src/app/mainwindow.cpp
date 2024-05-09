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
   this->add_file1 = new QPushButton(QString::number(this->counter), this);
   connect(this->add_file1, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(this->add_file1);

   QWidget *widget = new QWidget(this);
   widget->setLayout(layout);
   // this->setCentralWidget(widget);
}


MainWindow::~MainWindow() {
   delete this->add_file1;
   delete this->add_file2;
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


void MainWindow::onButtonClicked() {
   this->add_file1->setText(QString::number(++this->counter));
}
