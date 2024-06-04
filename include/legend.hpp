// Author: Dominik Sidorczuk

#ifndef LEGEND_HPP
#define LEGEND_HPP
#pragma once

#include <QDialog>
#include <QGridLayout>


struct LegendItem {
    QColor color;
    QString description;
};


class LegendDialog : public QDialog {
    Q_OBJECT

public:
    explicit LegendDialog(QWidget *parent = nullptr);
    void initLegend();

private:
    QGridLayout *dialogLayout;
    QVector<LegendItem> items;
};

#endif
