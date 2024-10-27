#include "colourframe.h"
#include "ui_colourframe.h"

#include "colourform.h"
#include "colourmodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

ColourFrame::ColourFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ColourFrame)
{
    ui->setupUi(this);

    loadData();
}

ColourFrame::~ColourFrame()
{
    delete ui;
}

void ColourFrame::on_addButton_clicked()
{
    ColourForm *form = new ColourForm(this);
    form->setWindowTitle("Add New Colour");

    form->exec();
    loadData();
}

void ColourFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->colourTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    ColourForm *form = new ColourForm(this, ui->colourTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Colour");
    form->exec();

    loadData();
}

void ColourFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->colourTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    ColourForm *form = new ColourForm(this, ui->colourTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View Colour");
    form->exec();

    loadData();
}

void ColourFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->colourTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    ColourModel model = ColourModel::load(ui->colourTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.name() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
 }

void ColourFrame::loadData()
{
    QSqlQuery query = ColourModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Colour");

    ui->colourTable->setModel(tableModel);
}

