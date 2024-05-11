#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QPushButton>


class Button : public QPushButton {
    Q_OBJECT
public:
    explicit Button(const QString &text, const int &row, const int &column, QWidget *parent = nullptr)
        : QPushButton(text, parent), row(row), column(column) {};
    int row;
    int column;
};


#endif
