#include <TWidget.hpp>
#include <QPainter>


TWidget::TWidget(QWidget *parent) : QWidget(parent) {
    this->text = "";
}


TWidget::TWidget(const File &file, QWidget *parent) : QWidget(parent), file(file) {
    this->text = QString::fromStdString(this->file.get_filename());

}


void TWidget::set_text(QString text) {
    this->text = text;
}


void TWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this); // Utwórz obiekt QPainter do rysowania
    QFont font = gen_font(11, true);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignLeft, this->text); // Narysuj tekst w środku widgetu
}


QLabel *gen_text(const QString &text, const int &size, const bool &if_bold, QWidget *parent) {
    QLabel *Label = new QLabel(text, parent);
    QFont font = gen_font(size, if_bold);
    Label->setFont(font);
   
    return Label;
}


QFont gen_font(const int &size, const bool &if_bold) {
   QFont font;
   font.setPointSize(size);
   font.setBold(if_bold);
   return font;
}
