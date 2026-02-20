#include "zodiacframe.h"
#include "ui_zodiacframe.h"

#include "zodiacform.h"
#include "zodiacmodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

ZodiacFrame::ZodiacFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ZodiacFrame)
{
    ui->setupUi(this);

    loadData();
}

ZodiacFrame::~ZodiacFrame()
{
    delete ui;
}

void ZodiacFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->zodiacTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    ZodiacForm *form = new ZodiacForm(this, ui->zodiacTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle(tr("View Zodiac"));
    form->exec();

    loadData();

}


void ZodiacFrame::on_addButton_clicked()
{
    ZodiacForm *form = new ZodiacForm(this);
    form->setWindowTitle(tr("Add New Zodiac"));

    form->exec();
    loadData();
}


void ZodiacFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->zodiacTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    ZodiacForm *form = new ZodiacForm(this, ui->zodiacTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle(tr("Edit Zodiac"));
    form->exec();

    loadData();
}


void ZodiacFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->zodiacTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    ZodiacModel model = ZodiacModel::load(ui->zodiacTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, tr("Please confirm"), tr("Are you sure you want to delete ") + 
                                            model.name() + tr("? This action cannot be undone."));
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}

void ZodiacFrame::loadData()
{
    QSqlQuery query = ZodiacModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Zodiac"));

    ui->zodiacTable->setModel(tableModel);
}


void ZodiacFrame::on_search_button_clicked()
{
    m_search_for = ui->search_line_edit->text();
    loadData();
}


void ZodiacFrame::on_zodiacTable_doubleClicked(const QModelIndex &index)
{
    on_editButton_clicked();
}

