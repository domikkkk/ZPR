#include <TWidget.hpp>


TWidget::TWidget(QWidget *parent)
    : QWidget(parent),
      layout(new QVBoxLayout(this)),
      button(new QPushButton(this)),
      textEdit(new QTextEdit(this)),
      scrollArea(new QScrollArea(this)) {

    this->button->setMaximumWidth(100);
    this->scrollArea->setWidget(this->textEdit);
    this->scrollArea->setWidgetResizable(true);
    this->textEdit->setWordWrapMode(QTextOption::NoWrap);
    this->textEdit->setReadOnly(true);
}


TWidget::TWidget(const File &file, QWidget *parent) : TWidget(parent) {
    this->file = file;

    this->titleLabel = new QLabel(QString::fromStdString(this->file.get_filename()), this);
    this->titleLabel->setFont(gen_font(11, false));
    this->titleLabel->setAlignment(Qt::AlignCenter);

    this->textEdit->setPlainText(QString::fromStdString(this->file.getText()));
    this->textEdit->hide();

    this->button->setText("Preview");
    this->connect(this->button, &QPushButton::clicked, this, &TWidget::preview);

    this->layout->addWidget(this->titleLabel);
    this->layout->addWidget(this->button, 0, Qt::AlignCenter);
    this->layout->addWidget(this->scrollArea);
    this->setLayout(this->layout);
}


TWidget::TWidget(const QString &text, QWidget *parent) : TWidget(parent) {
    this->textEdit->setPlainText(text);
    this->button->setText("Save");
    // podłączyć przycisk
    
    this->layout->addWidget(this->scrollArea);
    this->layout->addWidget(this->button, 0, Qt::AlignCenter);
    this->setLayout(this->layout);
}


void TWidget::hideText() {
    this->textEdit->hide();
    this->button->setText("Preview");
}


void TWidget::readText() {
    if (!this->file.was_read()) {
        this->file.read();
        this->textEdit->setText(QString::fromStdString(this->file.getText()));
    }
    return;
}


void TWidget::splitFile() {
    if (!this->file.wasSplited()) this->file.splitByParagraphs();
}


void TWidget::preview() {
    if (this->textEdit->isHidden()) {
        this->readText();
        this->textEdit->show();
        this->button->setText("Hide");
    } else {
        this->hideText();
    }
    std::cout << this->file.getBlocks().size() << '\n';
}


void TWidget::change_file(const QString &filename) {
    this->file.change_filename(filename.toStdString());
    this->titleLabel->setText(filename);
    if (!this->textEdit->isHidden()) {
        this->hideText();
    }
}


void TWidget::highlightTextRange(const int &from, const int &to, const QColor &color) {
    QTextCursor cursor = this->textEdit->textCursor();
    cursor.setPosition(from, QTextCursor::MoveAnchor);
    cursor.setPosition(to, QTextCursor::KeepAnchor);

    QTextCharFormat charFormat;
    charFormat.setBackground(color);
    cursor.setCharFormat(charFormat);
}


const File &TWidget::getFile() const {
    return this->file;
}


QLabel *gen_text(const QString &text, const int &size, const bool &if_bold, QWidget *parent) {
    QLabel *Label = new QLabel(text, parent);
    Label->setFont(gen_font(size, if_bold));
   
    return Label;
}


const QFont gen_font(const int &size, const bool &if_bold) {
   QFont font;
   font.setPointSize(size);
   font.setBold(if_bold);
   return font;
}
