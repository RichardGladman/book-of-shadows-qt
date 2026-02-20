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
    form->setWindowTitle(tr("View Note"));
    form->exec();

    loadData();
}


void NotesFrame::on_addButton_clicked()
{
    NoteForm *form = new NoteForm(this);
    form->setWindowTitle(tr("Add New Note"));

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
    form->setWindowTitle(tr("Edit Note"));
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


    int confirmed = QMessageBox::question(this, tr("Please confirm"), 
                            tr("Are you sure you want to delete ") + model.title() + tr("? This action cannot be undone."));
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }

}

void NotesFrame::loadData()
{
    QSqlQuery query = NoteModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Note"));

    ui->noteTable->setModel(tableModel);
}

void NotesFrame::on_search_button_clicked()
{
    m_search_for = ui->search_line_edit->text();
    loadData();
}


void NotesFrame::on_noteTable_doubleClicked(const QModelIndex &index)
{
    on_editButton_clicked();
}

