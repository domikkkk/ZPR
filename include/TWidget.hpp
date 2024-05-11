#ifndef TWIDGET_HPP
#define TWIDGET_HPP

#include <QWidget>


class TWidget : public QWidget {
    Q_OBJECT
public:
    TWidget(QWidget *parent = nullptr) : QWidget(parent) {};
    TWidget(QString text, QWidget *parent = nullptr) : QWidget(parent), text(text) {};
    void set_text(QString text);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString text;
};


#endif
