#include <legend.hpp>
#include <QLabel>
#include <namespaces.hpp>


LegendDialog::LegendDialog(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Legenda");
    this->resize(200, 100);
    this->dialogLayout = new QGridLayout(this);
    
    this->initLegend();

    for (int i = 0; i < this->items.size(); ++i) {

        QLabel *colorLabel = new QLabel(this);
        colorLabel->setFixedSize(20, 20);
        colorLabel->setStyleSheet("background-color: " + this->items[i].color.name());

        QLabel *descriptionLabel = new QLabel(this->items[i].description, this);

        this->dialogLayout->addWidget(colorLabel, i, 0, Qt::AlignCenter);
        this->dialogLayout->addWidget(descriptionLabel, i, 1, Qt::AlignLeft);
    }
}


void LegendDialog::initLegend() {
    this->items = {
        {Colors::RED, "Usunięcie"},
        {Colors::GREEN, "Dodanie"},
        {Colors::YELLOW, "Zmiana"},
    }; // do zmian pewnie
}
