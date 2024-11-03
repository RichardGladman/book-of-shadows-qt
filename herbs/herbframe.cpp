#include "herbframe.h"
#include "ui_herbframe.h"

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
