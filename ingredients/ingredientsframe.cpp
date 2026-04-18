#include "ingredientsframe.h"
#include "ui_ingredientsframe.h"

#include "ingredientsform.h"
#include "ingredientmodel.h"

#include <QDebug>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

IngredientsFrame::IngredientsFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::IngredientsFrame)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &IngredientsFrame::handleAddClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &IngredientsFrame::handleEditClicked);
    connect(ui->viewButton, &QPushButton::clicked, this, &IngredientsFrame::handleViewClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &IngredientsFrame::handleDeleteClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &IngredientsFrame::handleSearchClicked);
    connect(ui->ingredientsTable, &QTableView::doubleClicked, this, &IngredientsFrame::handleEditClicked);
	
	loadData();
}

IngredientsFrame::~IngredientsFrame()
{
    delete ui;
}

void IngredientsFrame::handleAddClicked()
{
    IngredientsForm * form = new IngredientsForm(this);
	form->setWindowTitle("Add New Ingredients Entry");
	
	form->exec();
	loadData();
}

void IngredientsFrame::handleEditClicked()
{
	QModelIndexList selectedRows = ui->ingredientsTable->selectionModel()->selectedIndexes();
	if (selectedRows.empty()) {
	    return;
	}

	IngredientsForm *form = new IngredientsForm(this, ui->ingredientsTable->model()->index(selectedRows.at(0).row(), 
																						0).data().toInt());
	form->setWindowTitle(tr("Edit Ingredients"));
	form->exec();

	loadData();
}

void IngredientsFrame::handleViewClicked()
{
	QModelIndexList selectedRows =
		ui->ingredientsTable->selectionModel()->selectedIndexes();
	if (selectedRows.empty()) {
		return;
	}

	IngredientsForm *form = new IngredientsForm(this,
									  ui->ingredientsTable->model()
										  ->index(selectedRows.at(0).row(), 0)
										  .data()
										  .toInt(),
									  "view");
	form->setWindowTitle(tr("View Ingredients Entry"));
	form->exec();

	loadData();
}

void IngredientsFrame::handleDeleteClicked()
{
QModelIndexList selectedRows =
	ui->ingredientsTable->selectionModel()->selectedIndexes();
	if (selectedRows.empty()) {
		return;
	}
	
	IngredientModel model =
		IngredientModel::load(ui->ingredientsTable->model()
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

void IngredientsFrame::handleSearchClicked()
{
	m_search_for = ui->searchLineEdit->text();
	loadData();
}

void IngredientsFrame::loadData()
{
	QSqlQuery query = IngredientModel::list(m_search_for);
	QSqlQueryModel *tableModel = new QSqlQueryModel(this);
	tableModel->setQuery(std::move(query));
	
	tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
	tableModel->setHeaderData(1, Qt::Horizontal, tr("Entry"));
	
	ui->ingredientsTable->setModel(tableModel);
	
}
