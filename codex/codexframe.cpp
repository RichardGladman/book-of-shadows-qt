#include "codexframe.h"
#include "ui_codexframe.h"

#include <qpushbutton.h>

CodexFrame::CodexFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::CodexFrame)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &CodexFrame::handleAddClicked);
}

CodexFrame::~CodexFrame()
{
    delete ui;
}

void CodexFrame::handleAddClicked()
{
}
