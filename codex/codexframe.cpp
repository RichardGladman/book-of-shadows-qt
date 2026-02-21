#include "codexframe.h"
#include "ui_codexframe.h"

#include <QDebug>
#include <qpushbutton.h>

CodexFrame::CodexFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::CodexFrame)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &CodexFrame::handleAddClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &CodexFrame::handleEditClicked);
    connect(ui->viewButton, &QPushButton::clicked, this, &CodexFrame::handleViewClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &CodexFrame::handleDeleteClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &CodexFrame::handleSearchClicked);
}

CodexFrame::~CodexFrame()
{
    delete ui;
}

void CodexFrame::handleAddClicked()
{
    qDebug() << "Add";
}

void CodexFrame::handleEditClicked()
{
    qDebug() << "Edit";
}

void CodexFrame::handleViewClicked()
{
    qDebug() << "View";
}

void CodexFrame::handleDeleteClicked()
{
    qDebug() << "Delete";
}

void CodexFrame::handleSearchClicked()
{
    qDebug() << "Search";
}
