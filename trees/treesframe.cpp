#include "treesframe.h"
#include "ui_treesframe.h"

TreesFrame::TreesFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::TreesFrame)
{
    ui->setupUi(this);
}

TreesFrame::~TreesFrame()
{
    delete ui;
}

void TreesFrame::on_viewButton_clicked()
{

}


void TreesFrame::on_addButton_clicked()
{

}


void TreesFrame::on_deleteButton_clicked()
{

}


void TreesFrame::on_editButton_clicked()
{

}

