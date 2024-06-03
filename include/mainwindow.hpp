#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#define WIDTH 7  // lepiej nieparzyste dać
#define TWIDGET_WIDTH WIDTH / 2  // połowa szerokości
#define TWIDGET_HEIGTH 4
#define ADDFILEBUTTON 1
#define RUNBUTTON 3
#define MERGEBUTTON 4
#define LEGEND 5

#include <QMainWindow>
#include <QGridLayout>
#include <vector>
#include <button.hpp>
#include <mergedWindow.hpp>


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_button(Button *button, void (MainWindow::*funtion)());
    void longRunningTask();

private:
    QGridLayout *layout;
    MergedWindow *mergedWindow;
    std::vector<Button*> buttons;
    int progress = 0;  // chyba będzie do usunięcia
    bool cancel = false;
    bool can_merge = false;

protected:
    void resizeEvent(QResizeEvent *event) override;
signals:

public slots:
    void addFile();
    void run();
    void onProgressDialogCanceled();
    void displayLegend();
    void merge();
};

#endif
