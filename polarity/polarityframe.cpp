#include "polarityframe.h"
#include "ui_polarityframe.h"

#include "polarityform.h"

PolarityFrame::PolarityFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PolarityFrame)
{
    ui->setupUi(this);
}

PolarityFrame::~PolarityFrame()
{
    delete ui;
}

void PolarityFrame::on_addButton_clicked()
{
    PolarityForm form = PolarityForm(this);
    form.setWindowTitle("Add New Polarity");

    form.exec();
}

