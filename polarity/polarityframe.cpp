#include "polarityframe.h"
#include "ui_polarityframe.h"

#include "polarityform.h"
#include "polaritymodel.h"
#include "polarityviewdialog.h"

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
    form.setWindowTitle("Add New Polarity");

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
    dialog->exec();
}

void PolarityFrame::loadData()
{
    QSqlQuery query = PolarityModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Name");

    ui->polarityTable->setModel(tableModel);
}

