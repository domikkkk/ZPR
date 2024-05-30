#ifndef TWIDGET_HPP
#define TWIDGET_HPP

#pragma once

#include <QWidget>
#include <compare_files/file.hpp>


class TWidget : public QWidget {
    Q_OBJECT
public:
    explicit TWidget(QWidget *parent = nullptr);
    TWidget(const File &file, QWidget *parent = nullptr);
    void set_text(QString text);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString text;
    File file;
};


#endif
