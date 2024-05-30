#include <button.hpp>


Button::Button(const QString &text, const int &row, const int &column, QWidget *parent):
    QPushButton(text, parent), row(row), column(column) {};
