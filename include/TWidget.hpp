#ifndef TWIDGET_HPP
#define TWIDGET_HPP

#pragma once

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <compare_files/file.hpp>


class TWidget : public QWidget {
    Q_OBJECT
public:
    explicit TWidget(QWidget *parent = nullptr);
    TWidget(const File &file, QWidget *parent = nullptr);
    TWidget(const QString &text, QWidget *parent = nullptr);
    void change_file(const QString &filename);
    void hideText();
    void readText();
    void highlightTextRange(const int &from, const int &to, const QColor &color);
    const File &getFile() const;
    int column = -1;

protected:

private:
    File file;
    QVBoxLayout *layout;
    QLabel *titleLabel;
    QPushButton *button;
    QTextEdit *textEdit;
    QScrollArea *scrollArea;

public slots:
    void preview();
};


QLabel *gen_text(const QString &text, const int &size, const bool &if_bold = false, QWidget *parent = nullptr);
const QFont gen_font(const int &size, const bool &if_bold);

#endif
