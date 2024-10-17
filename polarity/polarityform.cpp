#include "polarityform.h"
#include "ui_polarityform.h"

#include "polaritymodel.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

extern QString baseDir;

PolarityForm::PolarityForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PolarityForm)
{
    ui->setupUi(this);
}

PolarityForm::~PolarityForm()
{
    delete ui;
}

void PolarityForm::on_selectButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose image file");
    if (!fileName.isEmpty()) {
        ui->imageLineEdit->setText(fileName);
    }
}

void PolarityForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString meaning = ui->descriptionTextEdit->toPlainText();
    QString image = ui->imageLineEdit->text();

    QString finalImage;

    if (image.contains(baseDir)) {
        finalImage = image;
    } else {
        QList<QString> parts = image.split("/");
        QString filename = parts[parts.length() - 1];
        finalImage = baseDir + "/images/" + filename;

        QFile file(image);
        file.copy(finalImage);
    }

    PolarityModel model {name, meaning, finalImage};

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must not be empty.");
        return;
    }

    if (model.save()) {
        QMessageBox::information(this, "Success", "Polarity has been saved");

        ui->nameLineEdit->clear();
        ui->descriptionTextEdit->clear();
        ui->imageLineEdit->clear();
    } else {
        QMessageBox::critical(this, "Error", "Polarity not saved");
    }
}


void PolarityForm::on_closeButton_clicked()
{
    reject();
}

