#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

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
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
    void addFile();
    void run();

};

#endif
