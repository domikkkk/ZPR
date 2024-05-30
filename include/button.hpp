#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QPushButton>


class Button : public QPushButton {
    Q_OBJECT
public:
    Button(const QString &text, const int &row, const int &column, QWidget *parent = nullptr);
    int row;
    int column;
};


#endif
