#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#define WIDTH 7  // lepiej nieparzyste dać
#define TWIDGET_WIDTH WIDTH / 2

#include <QMainWindow>
#include <button.hpp>
#include <QGridLayout>
#include <vector>


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_button(Button *button, void (MainWindow::*funtion)());
    void remove_null_button();

private:
    QGridLayout *layout;
    std::vector<Button*> buttons;

protected:

signals:

public slots:
    void addFile();
    void run();

};

#endif
