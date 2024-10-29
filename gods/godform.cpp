#include "godform.h"
#include "ui_godform.h"

#include "../polarity/polaritymodel.h"

#include <QSqlQuery>

GodForm::GodForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GodForm)
{
    ui->setupUi(this);

    QSqlQuery query = PolarityModel::list();

    while (query.next()) {
        ui->polarityCombo->addItem(query.value(1).toString(), query.value(0).toInt());
    }
}

GodForm::~GodForm()
{
    delete ui;
}

void GodForm::on_closeButton_clicked()
{
    reject();
}

