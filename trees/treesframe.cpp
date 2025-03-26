#include "treesframe.h"
#include "ui_treesframe.h"

#include "treeform.h"
#include "treemodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

TreesFrame::TreesFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::TreesFrame)
{
    ui->setupUi(this);

    loadData();
}

TreesFrame::~TreesFrame()
{
    delete ui;
}

void TreesFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->treesTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    TreeForm *form = new TreeForm(this, ui->treesTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View Tree");
    form->exec();

    loadData();
}


void TreesFrame::on_addButton_clicked()
{
    TreeForm *form = new TreeForm(this);
    form->setWindowTitle("Add New Tree");

    form->exec();
    loadData();
}


void TreesFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->treesTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    TreeModel model = TreeModel::load(ui->treesTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.name() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}


void TreesFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->treesTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    TreeForm *form = new TreeForm(this, ui->treesTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Tree");
    form->exec();

    loadData();
}


void TreesFrame::loadData()
{
    QSqlQuery query = TreeModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Tree");

    ui->treesTable->setModel(tableModel);
}
