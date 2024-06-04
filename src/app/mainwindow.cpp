// Author: Dominik Sidorczuk

#include <mainwindow.hpp>
#include <QFileDialog>
#include <QProgressDialog>
#include <QtConcurrent/QtConcurrent>
#include <QCoreApplication>
#include <QMessageBox>
#include <TWidget.hpp>
#include <legend.hpp>
#include <namespaces.hpp>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   QLabel *welcome = gen_text("Witamy!", 24, true, this);  // Dodanie głównego napisu
   welcome->setAlignment(Qt::AlignHCenter);
   this->setWindowTitle("Komparator");
   this->resize(1200, 800);

   this->layout = new QGridLayout;

   this->add_button(new Button("Dodaj plik", MWindow::ADDFILEBUTTON_Y, MWindow::LEFT_ADDFILEBUTTON_X, this), &MainWindow::addFile);
   this->add_button(new Button("Dodaj plik", MWindow::ADDFILEBUTTON_Y, MWindow::RIGHT_ADDFILEBUTTON_X, this), &MainWindow::addFile);
   this->add_button(new Button("Porównaj", MWindow::RUNBUTTON_Y, MWindow::HALF_WIDTH, this), &MainWindow::run);
   this->add_button(new Button("Połącz", MWindow::MERGEBUTTON_Y, MWindow::HALF_WIDTH, this), &MainWindow::merge);
   this->add_button(new Button("Legenda", MWindow::LEGEND, MWindow::HALF_WIDTH, this), &MainWindow::displayLegend);
   for (auto button: this->buttons) button->setMaximumWidth(100);

   this->layout->setVerticalSpacing(20);
   this->layout->addWidget(welcome, 0, MWindow::HALF_WIDTH);  // w 0 wierszu, w środkowej kolumnie ustawiony napis

   this->layout->setRowStretch(2, 1);  // Rozciągnięcie
   for (int i = 0; i < MWindow::WIDTH; ++i) {
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
   QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik"), QDir::currentPath(), tr("Wszystkie pliki (*.*)"));

   int column = clickedButton->column - 1;
   QLayoutItem *item = this->layout->itemAtPosition(clickedButton->row + 1, column);
   if (item) {
      TWidget *twidget = qobject_cast<TWidget*>(item->widget());
      if (filePath.size() != 0) twidget->change_file(filePath);
      else return;
      twidget->update();
   } else {
      if (filePath.size() == 0) return;
      clickedButton->setText("Zmień plik");
      TWidget *textwidget = new TWidget(File(filePath.toStdString()), this);
      textwidget->setMaximumWidth(TWindow::WIDTH * this->width() / this->layout->columnCount());
      if (column < TWindow::WIDTH) {
         this->left = textwidget;
      } else {
         this->right = textwidget;
      }
      this->layout->addWidget(textwidget, clickedButton->row + 1, column, TWindow::HEIGTH, TWindow::WIDTH);
   }
   this->can_merge = false;
}


void MainWindow::resizeEvent(QResizeEvent *event) {
   QMainWindow::resizeEvent(event);
   QList<TWidget *> twidgets = this->centralWidget()->findChildren<TWidget *>();
   for (TWidget *t : twidgets) {
      t->setMaximumWidth(TWindow::WIDTH * this->width() / this->layout->columnCount());
   }
}


void MainWindow::run() {
   auto twidgets = this->centralWidget()->findChildren<TWidget *>();
   if (twidgets.size() < 2) {
      QMessageBox::warning(this, "Uwaga!", "Najpierw musisz dodać 2 pliki zanim uruchomisz.");
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

   QProgressDialog progressDialog("Działanie...", "Anuluj", 0, this->app.maxCount, this);
   progressDialog.setWindowModality(Qt::WindowModal);
   progressDialog.setWindowTitle("Postęp");
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
   this->app.compare();

   for (auto change: app.getChanges()) {
      for (auto c: change.getChanges()) {
         std::size_t pos = c.getPosition();
         switch(c.getType()) {
            case ChangeType::Addition:
               this->right->highlightTextRange(pos, pos + c.getText().size(), Colors::GREEN);
            break;
            case ChangeType::Deletion:
               this->left->highlightTextRange(pos, pos + c.getText().size(), Colors::RED);
            break;
            case ChangeType::Shift:
               this->right->highlightTextRange(change.getModified().getStartPos(), change.getModified().getStartPos() + c.getText().size(), Colors::YELLOW);
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
      QMessageBox::warning(this, "Uwaga!", "Najpierw musisz porównać zanim złączysz pliki.");
      return;
   }
   if (this->editied) {
      if (this->mergedWindow != 0) delete this->mergedWindow;
      std::string TextToMerge = this->left->getFile().getText();
      TWidget *mergedWidget = new TWidget(QString::fromStdString(TextToMerge), this);
      this->mergedWindow = new MergedWindow(mergedWidget, this);
      this->mergedWindow->merge(this->app.getChanges());
      this->editied = false;
   }
   
   this->mergedWindow->show();
}
