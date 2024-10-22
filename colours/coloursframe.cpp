#include "coloursframe.h"
#include "ui_coloursframe.h"

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
