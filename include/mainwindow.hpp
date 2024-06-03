#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#define WIDTH 7  // lepiej nieparzyste dać
#define TWIDGET_WIDTH WIDTH / 2  // połowa szerokości
#define TWIDGET_HEIGTH 3
#define ADDFILEBUTTON 1
#define RUNBUTTON 3
#define LEGEND 4

#include <QMainWindow>
#include <QGridLayout>
#include <vector>
#include <button.hpp>


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_button(Button *button, void (MainWindow::*funtion)());
    void longRunningTask();

private:
    QGridLayout *layout;
    std::vector<Button*> buttons;
    int progress = 0;  // chyba będzie do usunięcia
    bool cancel = false;

protected:
    void resizeEvent(QResizeEvent *event) override;
signals:

public slots:
    void addFile();
    void run();
    void onProgressDialogCanceled();
    void displayLegend();
};

#endif
