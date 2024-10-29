#include "godframe.h"
#include "ui_godframe.h"

#include "godform.h"

GodFrame::GodFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::GodFrame)
{
    ui->setupUi(this);
}

GodFrame::~GodFrame()
{
    delete ui;
}

void GodFrame::on_addButton_clicked()
{
    GodForm *form = new GodForm(this);
    form->setWindowTitle("Add New God");

    form->exec();
}

