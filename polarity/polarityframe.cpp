#include "polarityframe.h"
#include "ui_polarityframe.h"

#include "polarityform.h"
#include "polaritymodel.h"
#include "polarityviewdialog.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>

PolarityFrame::PolarityFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PolarityFrame)
{
    ui->setupUi(this);

    loadData();
}

PolarityFrame::~PolarityFrame()
{
    delete ui;
}

void PolarityFrame::on_addButton_clicked()
{
    PolarityForm form = PolarityForm(this);
    form.setWindowTitle(tr("Add New Polarity"));

    form.exec();
    loadData();
}

void PolarityFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->polarityTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    PolarityForm *form = new PolarityForm(this, ui->polarityTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle(tr("Edit Polarity"));
    form->exec();

    loadData();
}

void PolarityFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->polarityTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    PolarityViewDialog *dialog = new PolarityViewDialog(this, ui->polarityTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    dialog->setWindowTitle(tr("View Polarity"));
    dialog->exec();
}

void PolarityFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->polarityTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    PolarityModel model = PolarityModel::load(ui->polarityTable->model()->index(selectedRows.at(0).row(),0).data().toInt());

    int confirmed = QMessageBox::question(this, tr("Please confirm"), 
                            tr("Are you sure you want to delete ") + model.name() + tr("? This action cannot be undone."));
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}

void PolarityFrame::loadData()
{
    QSqlQuery query = PolarityModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Name"));

    ui->polarityTable->setModel(tableModel);
}


