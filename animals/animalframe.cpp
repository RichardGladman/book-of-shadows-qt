#include "animalframe.h"
#include "ui_animalframe.h"

AnimalFrame::AnimalFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AnimalFrame)
{
    ui->setupUi(this);
}

AnimalFrame::~AnimalFrame()
{
    delete ui;
}

void AnimalFrame::on_viewButton_clicked()
{

}


void AnimalFrame::on_addButton_clicked()
{

}


void AnimalFrame::on_editButton_clicked()
{

}


void AnimalFrame::on_deleteButton_clicked()
{

}

