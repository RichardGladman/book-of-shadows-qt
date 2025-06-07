#include "runestoneframe.h"
#include "ui_runestoneframe.h"

RunestoneFrame::RunestoneFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::RunestoneFrame)
{
    ui->setupUi(this);
}

RunestoneFrame::~RunestoneFrame()
{
    delete ui;
}

void RunestoneFrame::on_searchButton_clicked()
{

}


void RunestoneFrame::on_viewButton_clicked()
{

}


void RunestoneFrame::on_addButton_clicked()
{

}


void RunestoneFrame::on_editButton_clicked()
{

}


void RunestoneFrame::on_deleteButton_clicked()
{

}

