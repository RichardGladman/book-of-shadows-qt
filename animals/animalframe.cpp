#include "animalframe.h"
#include "ui_animalframe.h"

#include "animalform.h"
#include "animalmodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

AnimalFrame::AnimalFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AnimalFrame)
{
    ui->setupUi(this);
    loadData();
}

AnimalFrame::~AnimalFrame()
{
    delete ui;
}

void AnimalFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->animalsTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    AnimalForm *form = new AnimalForm(this, ui->animalsTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View Animal");
    form->exec();

    loadData();
}


void AnimalFrame::on_addButton_clicked()
{
    AnimalForm *form = new AnimalForm(this);
    form->setWindowTitle("Add New Animal");

    form->exec();
    loadData();

}


void AnimalFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->animalsTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    AnimalForm *form = new AnimalForm(this, ui->animalsTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Animal");
    form->exec();

    loadData();
}


void AnimalFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->animalsTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    AnimalModel model = AnimalModel::load(ui->animalsTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.name() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }

}

void AnimalFrame::on_searchPushButton_clicked()
{
    m_search_for = ui->searchLineEdit->text();
    loadData();
}

void AnimalFrame::loadData()
{
    QSqlQuery query = AnimalModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Animal");

    ui->animalsTable->setModel(tableModel);
}

