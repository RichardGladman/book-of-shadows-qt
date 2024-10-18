#include "polarityframe.h"
#include "ui_polarityframe.h"

#include "polarityform.h"
#include "polaritymodel.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>

PolarityFrame::PolarityFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PolarityFrame)
{
    ui->setupUi(this);

    loadData();
}

PolarityFrame::~PolarityFrame()
{
    delete ui;
}

void PolarityFrame::on_addButton_clicked()
{
    PolarityForm form = PolarityForm(this);
    form.setWindowTitle("Add New Polarity");

    form.exec();
}

void PolarityFrame::loadData()
{
    QSqlQuery query = PolarityModel::list();
    QSqlQueryModel *tableModel = new QSqlQueryModel(this);
    tableModel->setQuery(std::move(query));

    tableModel->setHeaderData(0, Qt::Horizontal, "Id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Name");

    ui->polarityTable->setModel(tableModel);
}
