#include "codexframe.h"
#include "ui_codexframe.h"

#include "codexform.h"
#include "codexmodel.h"

#include <QDebug>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

CodexFrame::CodexFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::CodexFrame)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &CodexFrame::handleAddClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &CodexFrame::handleEditClicked);
    connect(ui->viewButton, &QPushButton::clicked, this, &CodexFrame::handleViewClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &CodexFrame::handleDeleteClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &CodexFrame::handleSearchClicked);
    connect(ui->codexTable, &QTableView::doubleClicked, this, &CodexFrame::handleEditClicked);
	
	loadData();
}

CodexFrame::~CodexFrame()
{
    delete ui;
}

void CodexFrame::handleAddClicked()
{
    CodexForm * form = new CodexForm(this);
	form->setWindowTitle("Add New Codex Entry");
	
	form->exec();
	loadData();
}

void CodexFrame::handleEditClicked()
{
	QModelIndexList selectedRows = ui->codexTable->selectionModel()->selectedIndexes();
	if (selectedRows.empty()) {
	    return;
	}

	CodexForm *form = new CodexForm(this, ui->codexTable->model()->index(selectedRows.at(0).row(), 
																						0).data().toInt());
	form->setWindowTitle(tr("Edit Codex"));
	form->exec();

	loadData();
}

void CodexFrame::handleViewClicked()
{
	QModelIndexList selectedRows =
		ui->codexTable->selectionModel()->selectedIndexes();
	if (selectedRows.empty()) {
		return;
	}

	CodexForm *form = new CodexForm(this,
									  ui->codexTable->model()
										  ->index(selectedRows.at(0).row(), 0)
										  .data()
										  .toInt(),
									  "view");
	form->setWindowTitle(tr("View Codex Entry"));
	form->exec();

	loadData();
}

void CodexFrame::handleDeleteClicked()
{
QModelIndexList selectedRows =
	ui->codexTable->selectionModel()->selectedIndexes();
	if (selectedRows.empty()) {
		return;
	}
	
	CodexModel model =
		CodexModel::load(ui->codexTable->model()
							  ->index(selectedRows.at(0).row(), 0)
							  .data()
							  .toInt());
	
	int confirmed = QMessageBox::question(
		this, tr("Please confirm"),
		tr("Are you sure you want to delete ") + model.name() +
			tr("? This action cannot be undone."));
	if (confirmed == QMessageBox::Yes) {
		model.remove();
		loadData();
	}
}

void CodexFrame::handleSearchClicked()
{
	m_search_for = ui->searchLineEdit->text();
	loadData();
}

void CodexFrame::loadData()
{
	QSqlQuery query = CodexModel::list(m_search_for);
	QSqlQueryModel *tableModel = new QSqlQueryModel(this);
	tableModel->setQuery(std::move(query));
	
	tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
	tableModel->setHeaderData(1, Qt::Horizontal, tr("Entry"));
	
	ui->codexTable->setModel(tableModel);
	
}
