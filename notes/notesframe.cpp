#include "notesframe.h"
#include "ui_notesframe.h"


#include "noteform.h"
#include "notemodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

NotesFrame::NotesFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::NotesFrame)
{
    ui->setupUi(this);
    loadData();
}

NotesFrame::~NotesFrame()
{
    delete ui;
}

void NotesFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->noteTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    NoteForm *form = new NoteForm(this, ui->noteTable->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle("View Animal");
    form->exec();

    loadData();
}


void NotesFrame::on_addButton_clicked()
{
    NoteForm *form = new NoteForm(this);
    form->setWindowTitle("Add New Animal");

    form->exec();
    loadData();

}


void NotesFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->noteTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    NoteForm *form = new NoteForm(this, ui->noteTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle("Edit Animal");
    form->exec();

    loadData();
}


void NotesFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->noteTable->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    NoteModel model = NoteModel::load(ui->noteTable->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, "Please confirm", "Are you sure you want to delete " + model.title() + "? This action cannot be undone.");
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }

}

void NotesFrame::loadData()
{
    QSqlQuery query = NoteModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Note");

    ui->noteTable->setModel(tableModel);
}
