#ifndef TWIDGET_HPP
#define TWIDGET_HPP

#pragma once

#include <QWidget>
#include <QLabel>
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


QLabel *gen_text(const QString &text, const int &size, const bool &if_bold = false, QWidget *parent = nullptr);
QFont gen_font(const int &size, const bool &if_bold);

#endif
