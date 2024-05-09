#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>


struct Point {
    int x;
    int y;
    Point(const int &x, const int &y);
};


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void gen_text(const QString &text, const int &size, const bool &if_bold = false);

private:
    QPushButton *add_file1;
    QPushButton *add_file2;
    int counter = 0;

signals:

public slots:
    void onButtonClicked(); 

};

#endif
