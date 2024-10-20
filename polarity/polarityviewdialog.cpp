#include "polarityviewdialog.h"
#include "ui_polarityviewdialog.h"

#include "polaritymodel.h"

PolarityViewDialog::PolarityViewDialog(QWidget *parent, int id)
    : QDialog(parent)
    , ui(new Ui::PolarityViewDialog)
{
    ui->setupUi(this);

    PolarityModel model = PolarityModel::load(id);

    ui->nameLabel->setText(model.name());
    ui->meaningLabel->setText(model.meaning());

    QPixmap image(model.image());

    ui->imageLabel->setPixmap(image);
}

PolarityViewDialog::~PolarityViewDialog()
{
    delete ui;
}

void PolarityViewDialog::on_closeButton_clicked()
{
    reject();
}

