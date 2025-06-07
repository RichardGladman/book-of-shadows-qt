#include "runestoneform.h"
#include "ui_runestoneform.h"

RunestoneForm::RunestoneForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunestoneForm)
{
    ui->setupUi(this);
}

RunestoneForm::~RunestoneForm()
{
    delete ui;
}
