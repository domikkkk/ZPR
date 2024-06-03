#ifndef MERGEDWINDOW_HPP
#define MERGEDWINDOW_HPP
#pragma once

#include <QMainWindow>
#include <TWidget.hpp>
#include <QHBoxLayout>


class MergedWindow : public QMainWindow {
    Q_OBJECT

public:
    MergedWindow(TWidget *twidget, QWidget *parent = nullptr);

private:
    QVBoxLayout *vertical;
};


#endif
