#include <mainwindow.hpp>
#include <QFileDialog>
#include <QProgressDialog>
#include <QtConcurrent/QtConcurrent>
#include <QCoreApplication>
#include <QMessageBox>
#include <cmath>
#include <TWidget.hpp>
#include <legend.hpp>
#include <colors.hpp>
#include <compare_files/textdiff.hpp>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   this->mergedWindow = new MergedWindow(new TWidget);
   QLabel *welcome = gen_text("Welcome!", 24, true, this);  // Dodanie głównego napisu
   welcome->setAlignment(Qt::AlignHCenter);
   this->setWindowTitle("Files compare");
   this->resize(1200, 800);

   this->layout = new QGridLayout;

   this->add_button(new Button("Add file", ADDFILEBUTTON, TWIDGET_WIDTH / 2, this), &MainWindow::addFile);
   this->add_button(new Button("Add file", ADDFILEBUTTON, WIDTH / 2 + int(std::ceil(float(TWIDGET_WIDTH) / 2.f)), this), &MainWindow::addFile);
   this->add_button(new Button("Run", RUNBUTTON, TWIDGET_WIDTH, this), &MainWindow::run);
   this->add_button(new Button("Merge", MERGEBUTTON, TWIDGET_WIDTH, this), &MainWindow::merge);
   this->add_button(new Button("Legend", LEGEND, TWIDGET_WIDTH, this), &MainWindow::displayLegend);
   for (auto button: this->buttons) button->setMaximumWidth(100);

   this->layout->setVerticalSpacing(20);
   this->layout->addWidget(welcome, 0, TWIDGET_WIDTH);  // w 0 wierszu, w środkowej kolumnie ustawiony napis

   this->layout->setRowStretch(2, 1);  // Rozciągnięcie
   for (int i = 0; i < WIDTH; ++i) {
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
   delete this->mergedWindow;
}


void MainWindow::add_button(Button *button, void (MainWindow::*funtion)()) {
   this->connect(button, &QPushButton::clicked, this, funtion);
   this->layout->addWidget(button, button->row, button->column, 1, 1, Qt::AlignCenter);
   this->buttons.push_back(button);
}


void MainWindow::addFile() {
   Button *clickedButton = qobject_cast<Button *>(sender());
   QString filePath = QFileDialog::getOpenFileName(this, tr("Choose file"), QDir::currentPath(), tr("All files (*.*)"));

   int column = clickedButton->column - 1;
   QLayoutItem *item = this->layout->itemAtPosition(clickedButton->row + 1, column);
   this->can_merge = false;
   if (item) {
      TWidget *twidget = qobject_cast<TWidget*>(item->widget());
      if (filePath.size() != 0) twidget->change_file(filePath);
      twidget->update();
   } else {
      if (filePath.size() == 0) return;
      clickedButton->setText("Change file");
      TWidget *textwidget = new TWidget(File(filePath.toStdString()), this);
      textwidget->setMaximumWidth(TWIDGET_WIDTH * this->width() / this->layout->columnCount());
      if (column < TWIDGET_WIDTH) {
         this->left = textwidget;
      } else {
         this->right = textwidget;
      }
      this->layout->addWidget(textwidget, clickedButton->row + 1, column, TWIDGET_HEIGTH, TWIDGET_WIDTH);
   }
}


void MainWindow::resizeEvent(QResizeEvent *event) {
   QMainWindow::resizeEvent(event);
   QList<TWidget *> twidgets = this->centralWidget()->findChildren<TWidget *>();
   for (TWidget *t : twidgets) {
      t->setMaximumWidth(TWIDGET_WIDTH * this->width() / this->layout->columnCount());
   }
}


void MainWindow::run() {
   auto twidgets = this->centralWidget()->findChildren<TWidget *>();
   if (twidgets.size() < 2) {
      QMessageBox::warning(this, "Warning", "You must add two files before running.");
      return;
   }
   for (TWidget *t : twidgets) {
      t->readText();
      t->hideText();
      t->splitFile();
      t->clearHighLights();
   }
   File f1 = this->left->getFile();
   File f2 = this->right->getFile();
   this->app.setFiles(f1, f2);  // prepare file to compare
   this->app.calculateMaxCount();

   QProgressDialog progressDialog("Running...", "Cancel", 0, this->app.maxCount, this);
   progressDialog.setWindowModality(Qt::WindowModal);
   progressDialog.setWindowTitle("Progress");
   this->connect(&progressDialog, &QProgressDialog::canceled, this, &MainWindow::onProgressDialogCanceled);
   this->cancel = false;
   this->progress = 0;

   QFuture<void> future = QtConcurrent::run(this, &MainWindow::longRunningTask);
   while (!future.isFinished()) {
        progressDialog.setValue(this->app.counter);
   }

   progressDialog.close();
}


void MainWindow::onProgressDialogCanceled() {
   this->cancel = true;
}


void MainWindow::longRunningTask() {
   QList<TWidget *> twidgets = this->centralWidget()->findChildren<TWidget *>();
   std::vector<TextDiff> changes = this->app.compare();

   for (auto change: changes) {
      for (auto c: change.getChanges()) {
         switch(c.getType()) {
            case ChangeType::Addition:
            std::cout << c.getText() << ' ' << c.getPosition() <<'\n';
               this->right->highlightTextRange(c.getPosition(), c.getPosition() + c.getText().size(), Colors::GREEN);
            break;
            case ChangeType::Deletion:
               this->left->highlightTextRange(c.getPosition(), c.getPosition() + c.getText().size(), Colors::RED);
            break;
         }
      }
   }
   
   this->can_merge = true;
   this->editied = true;
   return;
}


void MainWindow::displayLegend() {
   LegendDialog legendDialog(this);
   legendDialog.exec();
}


void MainWindow::merge() {
   if (!this->can_merge) {
      QMessageBox::warning(this, "Warning", "You must run before merging.");
      return;
   }
   // merging
   if (this->editied) {
      delete this->mergedWindow;
      std::string mergedText = "Zmergowany jakiś tekst";
      TWidget *mergedWidget = new TWidget(QString::fromStdString(mergedText), this);
      this->mergedWindow = new MergedWindow(mergedWidget, this);
      this->editied = false;
   }
   
   this->mergedWindow->show();
}
