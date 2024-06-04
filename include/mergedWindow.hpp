#ifndef MERGEDWINDOW_HPP
#define MERGEDWINDOW_HPP
#pragma once

#include <QMainWindow>
#include <TWidget.hpp>
#include <QHBoxLayout>
#include <compare_files/textdiff.hpp>


class MergedWindow : public QMainWindow {
    Q_OBJECT

public:
    MergedWindow(TWidget *twidget, QWidget *parent = nullptr);
    void merge(const std::vector<TextDiff> &diffs);

private:
    TWidget *twidget;
    QVBoxLayout *verticalLayout;
};


#endif
