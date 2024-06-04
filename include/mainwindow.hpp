#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <vector>
#include <button.hpp>
#include <mergedWindow.hpp>
#include <compare_files/app.hpp>


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_button(Button *button, void (MainWindow::*funtion)());
    void longRunningTask();

private:
    QGridLayout *layout;
    MergedWindow *mergedWindow = 0;
    std::vector<Button*> buttons;
    TWidget *left;
    TWidget *right;
    App app;
    int progress = 0;  // chyba będzie do usunięcia
    bool cancel = false;
    bool can_merge = false;
    bool editied = false;

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
