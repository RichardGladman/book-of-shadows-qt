#include "tarotframe.h"
#include "ui_tarotframe.h"


#include <QMessageBox>
#include <QSqlQueryModel>

#include "tarotform.h"

TarotFrame::TarotFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::TarotFrame)
{
    ui->setupUi(this);

    loadData();
}

TarotFrame::~TarotFrame()
{
    delete ui;
}

void TarotFrame::on_searchButton_clicked()
{
    QString term = ui->searchlineEdit->text();
    loadData(term);
}


void TarotFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->tarotTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    TarotForm *form = new TarotForm(this, ui->tarotTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View Tarot");
    form->exec();
}


void TarotFrame::on_addButton_clicked()
{
    TarotForm *form = new TarotForm(this);
    form->setWindowTitle("Add New Tarot");

    form->exec();
    loadData();
}


void TarotFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->tarotTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    TarotForm *form = new TarotForm(this, ui->tarotTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Tarot");
    form->exec();

    loadData();
}


void TarotFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->tarotTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    TarotModel model = TarotModel::load(ui->tarotTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.name() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}

void TarotFrame::loadData(const QString &term)
{
    QSqlQuery query = TarotModel::list(term);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Rune");

    ui->tarotTable->setModel(tableModel);
}
