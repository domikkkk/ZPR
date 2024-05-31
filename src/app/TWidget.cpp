#include <TWidget.hpp>
#include <QVBoxLayout>


TWidget::TWidget(QWidget *parent)
    : QWidget(parent),
      titleLabel(new QLabel(this)),
      textEdit(new QTextEdit(this)),
      scrollArea(new QScrollArea(this)) {
    
    this->titleLabel->setAlignment(Qt::AlignCenter);
    this->scrollArea->setWidget(this->textEdit);
    this->scrollArea->setWidgetResizable(true);
    this->textEdit->setWordWrapMode(QTextOption::NoWrap);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(scrollArea);
    this->setLayout(layout);
}


TWidget::TWidget(const File &file, QWidget *parent) : TWidget(parent) {
    this->file = file;
    this->titleLabel->setText(QString::fromStdString(this->file.get_filename())); 
    this->titleLabel->setFont(gen_font(11, false));
    this->textEdit->setPlainText(QString::fromStdString(file.getText()));
}



QLabel *gen_text(const QString &text, const int &size, const bool &if_bold, QWidget *parent) {
    QLabel *Label = new QLabel(text, parent);
    Label->setFont(gen_font(size, if_bold));
   
    return Label;
}


QFont gen_font(const int &size, const bool &if_bold) {
   QFont font;
   font.setPointSize(size);
   font.setBold(if_bold);
   return font;
}
