#include "runestoneframe.h"
#include "ui_runestoneframe.h"

#include <QMessageBox>
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
    QModelIndexList selectedRows = ui->runestoneTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    RunestoneForm *form = new RunestoneForm(this, ui->runestoneTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View Runestone");
    form->exec();
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
    QModelIndexList selectedRows = ui->runestoneTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    RunestoneForm *form = new RunestoneForm(this, ui->runestoneTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Runestone");
    form->exec();

    loadData();
}


void RunestoneFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->runestoneTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    RunestoneModel model = RunestoneModel::load(ui->runestoneTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.name() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
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
