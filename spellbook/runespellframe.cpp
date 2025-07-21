#include "runespellframe.h"
#include "ui_runespellframe.h"

#include "runespellform.h"

RuneSpellFrame::RuneSpellFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::RuneSpellFrame)
{
    ui->setupUi(this);
}

RuneSpellFrame::~RuneSpellFrame()
{
    delete ui;
}

void RuneSpellFrame::on_addButton_clicked()
{
    RuneSpellForm *form = new RuneSpellForm(this);
    form->setWindowTitle("Add New Rune Spell");

    form->exec();
}

