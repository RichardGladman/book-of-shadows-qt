#include "herbframe.h"
#include "ui_herbframe.h"

#include "herbform.h"
#include "herbmodel.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

HerbFrame::HerbFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::HerbFrame)
{
    ui->setupUi(this);

    loadData();
}

HerbFrame::~HerbFrame()
{
    delete ui;
}

void HerbFrame::on_addButton_clicked()
{
    HerbForm *form = new HerbForm(this);
    form->setWindowTitle("Add New Herb");
    form->exec();
    loadData();
}

void HerbFrame::loadData()
{
    QSqlQuery query = HerbModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Herb");

    ui->HerbTable->setModel(tableModel);
}

