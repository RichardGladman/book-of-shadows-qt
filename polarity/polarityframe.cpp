#include "polarityframe.h"
#include "ui_polarityframe.h"

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
