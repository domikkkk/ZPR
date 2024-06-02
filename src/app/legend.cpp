#include <legend.hpp>
#include <QLabel>


LegendDialog::LegendDialog(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Legend");
    dialogLayout = new QGridLayout(this);
    
    this->initLegend();

    for (int i = 0; i < this->items.size(); ++i) {

        QLabel *colorLabel = new QLabel(this);
        colorLabel->setFixedSize(20, 20);
        colorLabel->setStyleSheet("background-color: " + this->items[i].color);

        QLabel *descriptionLabel = new QLabel(this->items[i].description, this);

        this->dialogLayout->addWidget(colorLabel, i, 0, Qt::AlignCenter);
        this->dialogLayout->addWidget(descriptionLabel, i, 1, Qt::AlignLeft);
    }
}


void LegendDialog::initLegend() {
    this->items = {
        {"red", "Error"},
        {"green", "Success"},
        {"blue", "Information"},
    }; // do zmian pewnie
}
