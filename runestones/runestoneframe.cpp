#include "runestoneframe.h"
#include "ui_runestoneframe.h"

#include "runestoneform.h"

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
    RunestoneForm *form = new RunestoneForm(this);
    form->setWindowTitle("Add New Runestone");

    form->exec();
}


void RunestoneFrame::on_editButton_clicked()
{

}


void RunestoneFrame::on_deleteButton_clicked()
{

}

