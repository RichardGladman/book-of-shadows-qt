#include "herbform.h"
#include "ui_herbform.h"

HerbForm::HerbForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HerbForm)
{
    ui->setupUi(this);
}

HerbForm::~HerbForm()
{
    delete ui;
}
