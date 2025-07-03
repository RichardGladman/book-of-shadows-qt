#include "runestoneframe.h"
#include "ui_runestoneframe.h"

#include <QSqlQueryModel>

#include "runestoneform.h"

RunestoneFrame::RunestoneFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::RunestoneFrame)
{
    ui->setupUi(this);

    loadData();
}

RunestoneFrame::~RunestoneFrame()
{
    delete ui;
}

void RunestoneFrame::on_searchButton_clicked()
{

}


void RunestoneFrame::on_viewButton_clicked()
{

}


void RunestoneFrame::on_addButton_clicked()
{
    RunestoneForm *form = new RunestoneForm(this);
    form->setWindowTitle("Add New Runestone");

    form->exec();
    loadData();
}


void RunestoneFrame::on_editButton_clicked()
{

}


void RunestoneFrame::on_deleteButton_clicked()
{

}

void RunestoneFrame::loadData()
{
    QSqlQuery query = RunestoneModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Rune");

    ui->runestoneTable->setModel(tableModel);
}
