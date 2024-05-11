#include <mainwindow.hpp>
#include <QFileDialog>
#include <algorithm>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   QLabel *welcome = this->gen_text("Welcome!", 24, true);  // Dodanie głównego napisu
   welcome->setAlignment(Qt::AlignHCenter);
   this->setWindowTitle("Files compare");
   this->resize(1200, 800);

   this->layout = new QGridLayout;

   this->add_button(new Button("Add file", 1, 0, this), &MainWindow::onButtonClicked);

   this->add_button(new Button("Add file", 1, 2, this), &MainWindow::onButtonClicked);

   this->layout->setVerticalSpacing(20);
   this->layout->addWidget(welcome, 0, 1);  // w 0 wierszu, w środkowej kolumnie 3 ustawiony napis

   this->layout->setRowStretch(2, 1);  // Zrobienie wolnego wiersza bo dlaczego nie
   for (int i = 0; i < this->layout->columnCount(); ++i) {
      this->layout->setColumnStretch(i, 1);
   }
   QWidget *widget = new QWidget(this);
   widget->setLayout(this->layout);
   this->setCentralWidget(widget);
}


MainWindow::~MainWindow() {
   QLayoutItem *child;
   while ((child = this->layout->takeAt(0)) != nullptr) {
      delete child->widget();
      delete child;
   }
   delete this->layout;
}


QLabel *MainWindow::gen_text(const QString &text, const int &size, const bool &if_bold) {
   QLabel *Label = new QLabel(text, this);

   QFont font = Label->font();
   font.setPointSize(size);
   font.setBold(if_bold);
   Label->setFont(font);
   
   return Label;
}


void MainWindow::add_button(Button *button, void (MainWindow::*funtion)()) {
   connect(button, &QPushButton::clicked, this, funtion);
   this->layout->addWidget(button, button->row, button->column, 1, 1);
   this->buttons.push_back(button);
}


void MainWindow::remove_null_button() {
   buttons.erase(std::remove_if(buttons.begin(), buttons.end(),
    [](Button* button) { return button == nullptr; }), buttons.end());
}


void MainWindow::onButtonClicked() {
   Button *clickedButton = qobject_cast<Button *>(sender());
   this->add_File(clickedButton);
}


void MainWindow::add_File(Button *button) {
   QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik"), QDir::currentPath(), tr("Wszystkie pliki (*.*)"));
   QFile file(filePath);
   QString fileContent;
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      fileContent = QString::fromUtf8(file.readAll());
      file.close();
   }
   QLabel *fileLabel = this->gen_text(fileContent, 11);
   fileLabel->setMaximumWidth(this->width() / this->layout->columnCount());
   fileLabel->setAlignment(Qt::AlignLeft);
   this->layout->addWidget(fileLabel, button->row, button->column, 2, 1);
   this->layout->removeWidget(button);
   delete button;
}


void MainWindow::resizeEvent(QResizeEvent *event) {
   // QList<QWidget *> widgets = this->findChildren<QWidget *>();
   QLayoutItem *item = this->layout->itemAtPosition(1, 0);
   if (item) {
      QWidget *widget = item->widget();
      if (widget) {
         widget->setMaximumWidth(this->width() / this->layout->columnCount());
      }
   }
   item = this->layout->itemAtPosition(1, 2);
   if (item) {
      QWidget *widget = item->widget();
      if (widget) {
         widget->setMaximumWidth(this->width() / this->layout->columnCount());
      }
   }
}
