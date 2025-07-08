#include "crystalframe.h"
#include "ui_crystalframe.h"

#include <QMessageBox>
#include <QSqlQueryModel>

#include "crystalform.h"

CrystalFrame::CrystalFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::CrystalFrame)
{
    ui->setupUi(this);

    loadData();
}

CrystalFrame::~CrystalFrame()
{
    delete ui;
}

void CrystalFrame::on_searchButton_clicked()
{
    QString term = ui->searchlineEdit->text();
    loadData(term);
}


void CrystalFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->crystalTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    CrystalForm *form = new CrystalForm(this, ui->crystalTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View Crystal");
    form->exec();
}


void CrystalFrame::on_addButton_clicked()
{
    CrystalForm *form = new CrystalForm(this);
    form->setWindowTitle("Add New Crystal");

    form->exec();
    loadData();
}


void CrystalFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->crystalTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    CrystalForm *form = new CrystalForm(this, ui->crystalTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Crystal");
    form->exec();

    loadData();
}


void CrystalFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->crystalTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    CrystalModel model = CrystalModel::load(ui->crystalTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.name() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}

void CrystalFrame::loadData(const QString &term)
{
    QSqlQuery query = CrystalModel::list(term);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Crystal");

    ui->crystalTable->setModel(tableModel);
}
