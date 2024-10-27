#include "godframe.h"
#include "ui_godframe.h"

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
