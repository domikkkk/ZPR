#ifndef TWIDGET_HPP
#define TWIDGET_HPP

#pragma once

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <compare_files/file.hpp>


class TWidget : public QWidget {
    Q_OBJECT
public:
    explicit TWidget(QWidget *parent = nullptr);
    TWidget(const File &file, QWidget *parent = nullptr);

protected:

private:
    File file;
    QLabel *titleLabel;
    QTextEdit *textEdit;
    QScrollArea *scrollArea;
};


QLabel *gen_text(const QString &text, const int &size, const bool &if_bold = false, QWidget *parent = nullptr);
QFont gen_font(const int &size, const bool &if_bold);

#endif
