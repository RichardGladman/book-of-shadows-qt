#include "godframe.h"
#include "ui_godframe.h"

#include "godform.h"
#include "godmodel.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

GodFrame::GodFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::GodFrame)
{
    ui->setupUi(this);

    loadData();
}

GodFrame::~GodFrame()
{
    delete ui;
}

void GodFrame::on_addButton_clicked()
{
    GodForm *form = new GodForm(this);
    form->setWindowTitle("Add New God");

    form->exec();
    loadData();
}

void GodFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->godTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    GodForm *form = new GodForm(this, ui->godTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit God");
    form->exec();

    loadData();

}

void GodFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->godTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    GodForm *form = new GodForm(this, ui->godTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View God");
    form->exec();

    loadData();
}

void GodFrame::loadData()
{
    QSqlQuery query = GodModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "God");

    ui->godTable->setModel(tableModel);

}
