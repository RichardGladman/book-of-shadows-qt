#include "herbframe.h"
#include "ui_herbframe.h"

#include "herbform.h"

HerbFrame::HerbFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::HerbFrame)
{
    ui->setupUi(this);
}

HerbFrame::~HerbFrame()
{
    delete ui;
}

void HerbFrame::on_addButton_clicked()
{
    HerbForm *form = new HerbForm(this);
    form->setWindowTitle("Add New Herb");
    form->exec();
}

