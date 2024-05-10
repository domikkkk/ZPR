#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>


struct Point {
    int x;
    int y;
    Point(const int &x, const int &y);
};


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLabel *gen_text(const QString &text, const int &size, const bool &if_bold = false);
    void add_File(QPushButton *button, const Point &p);

private:
    QPushButton *add_file1;
    QPushButton *add_file2;
    QGridLayout *layout;

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
    void onButton1Clicked();
    void onButton2Clicked(); 

};

#endif
