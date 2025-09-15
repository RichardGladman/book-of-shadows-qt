#include "runespellframe.h"
#include "ui_runespellframe.h"

#include "runespellform.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "runespellmodel.h"

RuneSpellFrame::RuneSpellFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::RuneSpellFrame)
{
    ui->setupUi(this);

    loadData();
}

RuneSpellFrame::~RuneSpellFrame()
{
    delete ui;
}

void RuneSpellFrame::on_addButton_clicked()
{
    RuneSpellForm *form = new RuneSpellForm(this);
    form->setWindowTitle("Add New Rune Spell");

    form->exec();
    loadData();
}

void RuneSpellFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->spellTableView->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    RuneSpellForm *form = new RuneSpellForm(this, ui->spellTableView->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Rune Spell");
    form->exec();

    loadData();
}

void RuneSpellFrame::loadData()
{
    QSqlQuery query = RunespellModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Spell Name");

    ui->spellTableView->setModel(tableModel);
}

void RuneSpellFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->spellTableView->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    RunespellModel model = RunespellModel::load(ui->spellTableView->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.title() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}

