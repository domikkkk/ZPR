#include <mainwindow.hpp>
#include <QFileDialog>
#include <algorithm>
#include <TWidget.hpp>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   QLabel *welcome = this->gen_text("Welcome!", 24, true);  // Dodanie głównego napisu
   welcome->setAlignment(Qt::AlignHCenter);
   this->setWindowTitle("Files compare");
   this->resize(1200, 800);

   this->layout = new QGridLayout;

   this->add_button(new Button("Add file", 1, 1, this), &MainWindow::onButtonClicked);
   this->add_button(new Button("Add file", 1, 3, this), &MainWindow::onButtonClicked);
   this->add_button(new Button("Run", 3, 2, this), &MainWindow::run);

   this->layout->setVerticalSpacing(20);
   this->layout->addWidget(welcome, 0, 2);  // w 0 wierszu, w środkowej kolumnie ustawiony napis

   this->layout->setRowStretch(2, 1);  // Zrobienie wolnego wiersza bo dlaczego nie
   this->layout->setColumnStretch(4, 1);  // Żeby było równo
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
   this->connect(button, &QPushButton::clicked, this, funtion);
   this->layout->addWidget(button, button->row, button->column, 1, 1);
   this->buttons.push_back(button);
}


void MainWindow::remove_null_button() {
   this->buttons.erase(std::remove_if(this->buttons.begin(), this->buttons.end(),
    [](Button* button) { return button == nullptr; }), this->buttons.end());
}


void MainWindow::onButtonClicked() {
   Button *clickedButton = qobject_cast<Button *>(sender());
   this->add_File(clickedButton);
}


void MainWindow::run() {

}


void MainWindow::add_File(Button *button) {
   QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik"), QDir::currentPath(), tr("Wszystkie pliki (*.*)"));
   // QFile file(filePath);
   // QString fileContent;
   // if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
   //    fileContent = QString::fromUtf8(file.readAll());
   //    file.close();
   // TODO reading file to -> class File
   // }
   QLayoutItem *item = this->layout->itemAtPosition(button->row + 1, button->column - 1);
   if (item) {
      QWidget *widget = item->widget(); // Pobranie widgetu z elementu układu
      TWidget *twidget = qobject_cast<TWidget*>(widget); // Rzutowanie widgetu na QLabel
      if (twidget) {
            twidget->set_text(filePath);
            twidget->update();
      }
   } else {
      // QLabel *fileLabel = this->gen_text(filePath, 11);
      TWidget *twidget = new TWidget(filePath, this);
      twidget->setMaximumWidth(2 * this->width() / this->layout->columnCount());
      this->layout->addWidget(twidget, button->row + 1, button->column - 1, 2, 2);
   }
}


void MainWindow::resizeEvent(QResizeEvent *event) {
   // QList<QWidget *> widgets = this->findChildren<QWidget *>();
   QLayoutItem *item = this->layout->itemAtPosition(1, 1);
   if (item) {
      QWidget *widget = item->widget();
      if (widget) {
         widget->setMaximumWidth(2 * this->width() / this->layout->columnCount());
      }
   }
   item = this->layout->itemAtPosition(1, 3);
   if (item) {
      QWidget *widget = item->widget();
      if (widget) {
         widget->setMaximumWidth(2 * this->width() / this->layout->columnCount());
      }
   }
}
