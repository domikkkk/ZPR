#include <TWidget.hpp>
#include <QVBoxLayout>


TWidget::TWidget(QWidget *parent)
    : QWidget(parent),
      titleLabel(new QLabel(this)),
      button(new QPushButton("Preview", this)),
      textEdit(new QTextEdit(this)),
      scrollArea(new QScrollArea(this)) {
    
    this->titleLabel->setAlignment(Qt::AlignCenter);
    this->button->setMaximumWidth(100);
    this->connect(this->button, &QPushButton::clicked, this, &TWidget::preview);
    this->scrollArea->setWidget(this->textEdit);
    this->scrollArea->setWidgetResizable(true);
    this->textEdit->setWordWrapMode(QTextOption::NoWrap);
    this->textEdit->hide();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(this->titleLabel);
    layout->addWidget(this->button, 0, Qt::AlignCenter);
    layout->addWidget(this->scrollArea);
    this->setLayout(layout);
}


TWidget::TWidget(const File &file, QWidget *parent) : TWidget(parent) {
    this->file = file;
    this->titleLabel->setText(QString::fromStdString(this->file.get_filename())); 
    this->titleLabel->setFont(gen_font(11, false));
    this->textEdit->setPlainText(QString::fromStdString(this->file.getText()));
}


void TWidget::hideText() {
    this->textEdit->hide();
    this->button->setText("Preview");
}


void TWidget::preview() {
    if (this->textEdit->isHidden()) {
        if (!this->file.was_read()) {
            this->file.read();
        }
        this->textEdit->setText(QString::fromStdString(this->file.getText()));
        this->textEdit->show();
        this->button->setText("Hide");
    } else {
        this->hideText();
    }
}


void TWidget::change_file(const QString &filename) {
    this->file.change_filename(filename.toStdString());
    this->titleLabel->setText(filename);
    if (!this->textEdit->isHidden()) {
        this->hideText();
    }
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
