#include <legend.hpp>
#include <QLabel>
#include <colors.hpp>


LegendDialog::LegendDialog(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Legend");
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
        {Colors::RED, "Zmiana1"},
        {Colors::GREEN, "Zmiana2"},
        {Colors::BLUE, "Zmiana3"},
        {Colors::YELLOW, "Zmiana4"},
    }; // do zmian pewnie
}
