#include "planetsframe.h"
#include "ui_planetsframe.h"

#include "planetform.h"
#include "planetmodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

PlanetsFrame::PlanetsFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PlanetsFrame)
{
    ui->setupUi(this);

    loadData();
}

PlanetsFrame::~PlanetsFrame()
{
    delete ui;
}

void PlanetsFrame::on_addButton_clicked()
{
    PlanetForm *form = new PlanetForm(this);
    form->setWindowTitle(tr("Add new Planet"));

    form->exec();

    loadData();
}


void PlanetsFrame::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->planetsTableView->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    PlanetForm *form = new PlanetForm(this, ui->planetsTableView->model()->index(selectedRows.at(0).row(), 0).data().toInt());
    form->setWindowTitle(tr("Edit Planet"));
    form->exec();

    loadData();
}


void PlanetsFrame::on_viewButton_clicked()
{
    QModelIndexList selectedRows = ui->planetsTableView->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    PlanetForm *form = new PlanetForm(this, ui->planetsTableView->model()->index(selectedRows.at(0).row(), 0).data().toInt(), "view");
    form->setWindowTitle(tr("View Planet"));
    form->exec();

    loadData();
}


void PlanetsFrame::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->planetsTableView->selectionModel()->selectedIndexes();
    if (selectedRows.empty()) {
        return;
    }

    PlanetModel model = PlanetModel::load(ui->planetsTableView->model()->index(selectedRows.at(0).row(), 0).data().toInt());


    int confirmed = QMessageBox::question(this, tr("Please confirm"), tr("Are you sure you want to delete ")
                         + model.name() + tr("? This action cannot be undone."));
    if (confirmed == QMessageBox::Yes) {
        model.remove();
        loadData();
    }
}

void PlanetsFrame::loadData()
{
    QSqlQuery query = PlanetModel::list(m_search_for);
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Planet"));

    ui->planetsTableView->setModel(tableModel);
}


void PlanetsFrame::on_search_button_clicked()
{
    m_search_for = ui->search_line_edit->text();
    loadData();
}


void PlanetsFrame::on_planetsTableView_doubleClicked(const QModelIndex &index)
{
    on_editButton_clicked();
}

