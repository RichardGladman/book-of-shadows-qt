#include "herbframe.h"
#include "ui_herbframe.h"

#include "herbform.h"
#include "herbmodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

HerbFrame::HerbFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::HerbFrame)
{
    ui->setupUi(this);

    loadData();
}

HerbFrame::~HerbFrame()
{
    delete ui;
}

void HerbFrame::on_addButton_clicked()
{
    HerbForm *form = new HerbForm(this);
    form->setWindowTitle(tr("Add New Herb"));
    form->exec();
    loadData();
}

void HerbFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->HerbTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    HerbForm *form = new HerbForm(this, ui->HerbTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle(tr("Edit Herb"));
    form->exec();

    loadData();
}

void HerbFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->HerbTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    HerbForm *form = new HerbForm(this, ui->HerbTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle(tr("View Herb"));
    form->exec();
}

void HerbFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->HerbTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    HerbModel model = HerbModel::load(ui->HerbTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, tr("Please confirm"), tr("Are you sure you want to delete ") + 
                model.name() + tr("? This action cannot be undone."));
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }

}

void HerbFrame::loadData()
{
    QSqlQuery query = HerbModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Herb");

    ui->HerbTable->setModel(tableModel);
}

void HerbFrame::on_search_button_clicked()
{
    m_search_for = ui->search_line_edit->text();
    loadData();
}


void HerbFrame::on_HerbTable_doubleClicked(const QModelIndex &index)
{
    on_editButton_clicked();
}

