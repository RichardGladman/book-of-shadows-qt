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
    form->setWindowTitle(tr("View Tree"));
    form->exec();

    loadData();
}


void TreesFrame::on_addButton_clicked()
{
    TreeForm *form = new TreeForm(this);
    form->setWindowTitle(tr("Add New Tree"));

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


    int confirmed = QMessageBox::question(this, tr("Please confirm"), tr("Are you sure you want to delete ") + 
                                            model.name() + tr("? This action cannot be undone."));
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
    form->setWindowTitle(tr("Edit Tree"));
    form->exec();

    loadData();
}


void TreesFrame::loadData()
{
    QSqlQuery query = TreeModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Tree"));

    ui->treesTable->setModel(tableModel);
}

void TreesFrame::on_search_button_clicked()
{
    m_search_for = ui->search_line_edit->text();
    loadData();
}

