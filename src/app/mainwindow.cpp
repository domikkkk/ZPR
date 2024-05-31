#include <mainwindow.hpp>
#include <QFileDialog>
#include <algorithm>
#include <TWidget.hpp>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   QLabel *welcome = gen_text("Welcome!", 24, true, this);  // Dodanie głównego napisu
   welcome->setAlignment(Qt::AlignHCenter);
   this->setWindowTitle("Files compare");
   this->resize(1200, 800);

   this->layout = new QGridLayout;

   this->add_button(new Button("Add file", 1, TWIDGET_WIDTH / 2, this), &MainWindow::addFile);
   this->add_button(new Button("Add file", 1, WIDTH / 2 + TWIDGET_WIDTH / 2 + 1, this), &MainWindow::addFile);
   this->add_button(new Button("Run", 3, TWIDGET_WIDTH, this), &MainWindow::run);

   this->layout->setVerticalSpacing(20);
   this->layout->addWidget(welcome, 0, TWIDGET_WIDTH);  // w 0 wierszu, w środkowej kolumnie ustawiony napis

   this->layout->setRowStretch(2, 1);  // Zrobienie wolnego wiersza bo dlaczego nie
   this->layout->setColumnStretch(WIDTH - 1, 1);  // Żeby było równo
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


void MainWindow::add_button(Button *button, void (MainWindow::*funtion)()) {
   this->connect(button, &QPushButton::clicked, this, funtion);
   this->layout->addWidget(button, button->row, button->column, 1, 1);
   this->buttons.push_back(button);
}


void MainWindow::remove_null_button() {
   this->buttons.erase(std::remove_if(this->buttons.begin(), this->buttons.end(),
    [](Button* button) { return button == nullptr; }), this->buttons.end());
}


void MainWindow::addFile() {
   Button *clickedButton = qobject_cast<Button *>(sender());
   QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik"), QDir::currentPath(), tr("Wszystkie pliki (*.*)"));

   QLayoutItem *item = this->layout->itemAtPosition(clickedButton->row + 1, clickedButton->column - 1);
   if (item) {
      TWidget *twidget = static_cast<TWidget*>(item->widget()); // Pobranie widgetu z elementu układu
      twidget->set_text(filePath);
      twidget->update();
   } else {
      TWidget *textwidget = new TWidget(File(filePath.toStdString()), this);
      textwidget->setMaximumWidth(2 * this->width() / this->layout->columnCount());
      this->layout->addWidget(textwidget, clickedButton->row + 1, clickedButton->column - 1, 2, TWIDGET_WIDTH);
   }
   // zmienić label na coś innego jak kliknie run
}


void MainWindow::run() {
   // wywołać główną funkcję porównującą pliki
}


void MainWindow::resizeEvent(QResizeEvent *event) {
   // QList<QWidget *> widgets = this->findChildren<QWidget *>();
   QLayoutItem *item = this->layout->itemAtPosition(1, 1);
   if (item) {
      QWidget *widget = item->widget();
      if (widget) {
         widget->setMaximumWidth(TWIDGET_WIDTH * this->width() / this->layout->columnCount());
      }
   }
   item = this->layout->itemAtPosition(1, 3);
   if (item) {
      QWidget *widget = item->widget();
      if (widget) {
         widget->setMaximumWidth(TWIDGET_WIDTH * this->width() / this->layout->columnCount());
      }
   }

   // TODO zmienić żeby leciało po elementach z na widgecie a nie statycznie się odwoływało do konkretnych punktów
}
