#include <mergedWindow.hpp>
#include <QVBoxLayout>
#include <QScrollArea>


MergedWindow::MergedWindow(TWidget *twidget, QWidget *parent): QMainWindow(parent) {
    this->setWindowTitle("Merged Text");
    this->resize(800, 600);
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(centralWidget);

    // TWidget po lewej stronie
    horizontalLayout->addWidget(twidget, 2);

    // Sekcja z przyciskami po prawej stronie
    QWidget *buttonContainer = new QWidget(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(buttonContainer);

    // Dodawanie przycisków do sekcji z przewijaniem
    for (int i = 0; i < 5; ++i) {
        QPushButton *button1 = new QPushButton("Original", buttonContainer);
        QPushButton *button2 = new QPushButton("Modified", buttonContainer);
        button1->setMaximumWidth(100);
        button2->setMaximumWidth(100);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(button1, 0, Qt::AlignCenter);
        buttonLayout->addWidget(button2, 0, Qt::AlignCenter);
        verticalLayout->addLayout(buttonLayout);
    }

    // Ustawienie układu dla kontenera przycisków
    buttonContainer->setLayout(verticalLayout);

    // Dodanie kontenera przycisków do przewijalnego obszaru
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(buttonContainer);
    scrollArea->setWidgetResizable(true);

    // Dodanie przewijalnego obszaru do głównego układu
    horizontalLayout->addWidget(scrollArea, 1);

    // Ustawienie głównego widgetu centralnego
    centralWidget->setLayout(horizontalLayout);
    this->setCentralWidget(centralWidget);
}
