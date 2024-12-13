#include "planetsframe.h"
#include "ui_planetsframe.h"

PlanetsFrame::PlanetsFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PlanetsFrame)
{
    ui->setupUi(this);
}

PlanetsFrame::~PlanetsFrame()
{
    delete ui;
}
