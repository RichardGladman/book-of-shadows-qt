#include "godframe.h"
#include "ui_godframe.h"

#include "godform.h"
#include "godmodel.h"

#include <QMessageBox>
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
    form->setWindowTitle(tr("Add New God"));

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
    form->setWindowTitle(tr("Edit God"));
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
    form->setWindowTitle(tr("View God"));
    form->exec();

    loadData();
}

void GodFrame::loadData()
{
    QSqlQuery query = GodModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "God");

    ui->godTable->setModel(tableModel);

}

void GodFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->godTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    GodModel model = GodModel::load(ui->godTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, tr("Please confirm"), 
        tr("Are you sure you want to delete ") + model.name() + tr("? This action cannot be undone."));
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}


void GodFrame::on_search_button_clicked()
{
    m_search_for = ui->search_line_edit->text();
    loadData();
}


void GodFrame::on_godTable_doubleClicked(const QModelIndex &index)
{
    on_editButton_clicked();
}

