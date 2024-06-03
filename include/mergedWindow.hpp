#ifndef MERGEDWINDOW_HPP
#define MERGEDWINDOW_HPP
#pragma once

#include <QMainWindow>
#include <TWidget.hpp>


class MergedWindow : public QMainWindow {
    Q_OBJECT

public:
    MergedWindow(QWidget *parent = nullptr);
    void addTWidget(TWidget *twidget);
};


#endif
