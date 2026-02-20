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
    form->setWindowTitle(tr("Add New Colour"));

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
    form->setWindowTitle(tr("Edit Colour"));
    form->exec();

    loadData();
}

void ColourFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->colourTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    ColourForm *form = new ColourForm(this, ui->colourTable->model()->index(selectedRows.at(0).row(), 
                                0).data().toInt(), "view");
    form->setWindowTitle(tr("View Colour"));
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


    int confirmed = QMessageBox::question(this, tr("Please confirm"), tr("Are you sure you want to delete ") + 
                                        model.name() + tr("? This action cannot be undone."));
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
 }

void ColourFrame::on_search_button_clicked()
{
    m_search_for = ui->search_lin_edit->text();
    loadData();
}

void ColourFrame::loadData()
{
    QSqlQuery query = ColourModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Colour");

    ui->colourTable->setModel(tableModel);
}


void ColourFrame::on_colourTable_doubleClicked(const QModelIndex &index)
{
    on_editButton_clicked();
}

