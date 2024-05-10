#include <mainwindow.hpp>
#include <QWidget>
#include <QFileDialog>


Point::Point(const int &x, const int &y) {
   this->x = x;
   this->y = y;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   QLabel *welcome = this->gen_text("Welcome!", 24, true);  // Dodanie głównego napisu
   this->setWindowTitle("Files compare");
   this->resize(1200, 800);
     // Stworzenie siatki
   this->layout = new QGridLayout;
   //  Dodanie 1 przycisku
   this->add_file1 = new QPushButton("Dodaj plik", this);
   connect(this->add_file1, &QPushButton::clicked, this, &MainWindow::onButton1Clicked);
   //  Dodanie 2 przycisku
   this->add_file2 = new QPushButton("Dodaj plik", this);
   connect(this->add_file2, &QPushButton::clicked, this, &MainWindow::onButton2Clicked);

   this->layout->setVerticalSpacing(20);
   this->layout->addWidget(welcome, 0, 1);  // w 0 wierszu, w środkowej kolumnie (1) ustawiony napis
   this->layout->addWidget(this->add_file1, 1, 0);  // w 1 wierszu, w 0 kolumnie pierwszy przycisk
   this->layout->addWidget(this->add_file2, 1, 2);  // w 1 wierszu, w 2 kolumnie drugi przycisk
   this->layout->setRowStretch(2, 1);  // Zrobienie wolnego wiersza bo dlaczego nie

   QWidget *widget = new QWidget(this);
   widget->setLayout(this->layout);
   this->setCentralWidget(widget);
}


MainWindow::~MainWindow() {
   // if (this->add_file1 != nullptr) delete this->add_file1;
   // if (this->add_file2 != nullptr) delete this->add_file2;
   QLayoutItem *child;
   while ((child = this->layout->takeAt(0)) != nullptr) {
      delete child->widget();
      delete child;
   }

   delete this->layout;
}


QLabel *MainWindow::gen_text(const QString &text, const int &size, const bool &if_bold) {
   QLabel *Label = new QLabel(text, this);
   Label->setAlignment(Qt::AlignHCenter);

   QFont font = Label->font();
   font.setPointSize(size);
   font.setBold(if_bold);
   Label->setFont(font);
   
   return Label;
}


void MainWindow::onButton1Clicked() {
   this->add_File(this->add_file1, {1, 0});
}


void MainWindow::onButton2Clicked() {
   this->add_File(this->add_file2, {1, 2});
}


void MainWindow::add_File(QPushButton *button, const Point &p) {
   QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik"), QDir::currentPath(), tr("Wszystkie pliki (*.*)"));
   if (!filePath.isEmpty()) {
      QLabel *fileLabel = new QLabel(filePath, this);
      layout->addWidget(fileLabel, p.x, p.y);
      layout->removeWidget(button);
      delete button;
   }
}


void MainWindow::resizeEvent(QResizeEvent *event) {
   QWidget::resizeEvent(event);
   // QList<QWidget *> widgets = this->findChildren<QWidget *>();
   // Można dalej nadpisać
}
