#include "coloursframe.h"
#include "ui_coloursframe.h"

#include "colourform.h"

ColoursFrame::ColoursFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ColoursFrame)
{
    ui->setupUi(this);
}

ColoursFrame::~ColoursFrame()
{
    delete ui;
}

void ColoursFrame::on_addButton_clicked()
{
    ColourForm *form = new ColourForm(this);
    form->setWindowTitle("Add New Colour");

    form->exec();
}

