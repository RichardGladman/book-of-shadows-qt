#include "colourframe.h"
#include "ui_colourframe.h"

#include "colourform.h"
#include "colourmodel.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

ColourFrame::ColourFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ColourFrame)
{
    ui->setupUi(this);

    loadData();
}

ColourFrame::~ColourFrame()
{
    delete ui;
}

void ColourFrame::on_addButton_clicked()
{
    ColourForm *form = new ColourForm(this);
    form->setWindowTitle("Add New Colour");

    form->exec();
    loadData();
}

void ColourFrame::loadData()
{
    QSqlQuery query = ColourModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Colour");

    ui->colourTable->setModel(tableModel);
}

