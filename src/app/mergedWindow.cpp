#include <mergedWindow.hpp>
#include <QVBoxLayout>
#include <QScrollArea>
#include <algorithm>
#include <namespaces.hpp>


MergedWindow::MergedWindow(TWidget *twidget, QWidget *parent): QMainWindow(parent), twidget(twidget) {
    this->setWindowTitle("Łączony tekst");
    this->resize(1200, 800);
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(centralWidget);

    horizontalLayout->addWidget(twidget, 2);

    // Sekcja z przyciskami po prawej stronie
    QWidget *changescontainer = new QWidget(this);
    this->verticalLayout = new QVBoxLayout(changescontainer);

    QLabel *title = gen_text("Dodanie", 18, true, this);
    title->setAlignment(Qt::AlignCenter);
    this->verticalLayout->addWidget(title);

    // Ustawienie układu dla kontenera przycisków
    changescontainer->setLayout(this->verticalLayout);

    // Dodanie kontenera przycisków do przewijalnego obszaru
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(changescontainer);
    scrollArea->setWidgetResizable(true);

    // Dodanie przewijalnego obszaru do głównego układu
    horizontalLayout->addWidget(scrollArea, 1);

    // Ustawienie głównego widgetu centralnego
    centralWidget->setLayout(horizontalLayout);
    this->setCentralWidget(centralWidget);
}


void MergedWindow::merge(const std::vector<TextDiff> &diffs) {
    for (const TextDiff &diff : diffs) {
        bool wasAdd = false;
        std::string newText = "";
        for (const Change &change : diff.getChanges()) {
            if (change.getType() == ChangeType::Addition) {
                newText += change.getText();
                wasAdd = true;
            } else {
                this->twidget->highlightTextRange(change.getPosition(), change.getPosition() + change.getText().size(), Colors::RED);
            }
        }
        if (wasAdd) {
            QTextEdit *textEdit = new QTextEdit(this);
            textEdit->setWordWrapMode(QTextOption::NoWrap);
            textEdit->setReadOnly(true);
            textEdit->setPlainText(QString::fromStdString(newText));
            QScrollArea *scrollArea = new QScrollArea(this);
            scrollArea->setWidget(textEdit);
            scrollArea->setWidgetResizable(true);
            this->verticalLayout->addWidget(scrollArea);
        }
    }
}
