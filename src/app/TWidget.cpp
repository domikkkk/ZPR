#include <TWidget.hpp>
#include <QPainter>


void TWidget::set_text(QString text) {
    this->text = text;
}

void TWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this); // Utwórz obiekt QPainter do rysowania
    painter.setFont(this->font());
    painter.drawText(rect(), Qt::AlignLeft, this->text); // Narysuj tekst w środku widgetu
}
