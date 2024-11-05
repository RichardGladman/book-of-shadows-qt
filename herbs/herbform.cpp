#include "herbform.h"
#include "ui_herbform.h"

#include "herbmodel.h"

#include <QMessageBox>

HerbForm::HerbForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HerbForm)
{
    ui->setupUi(this);
}

HerbForm::~HerbForm()
{
    delete ui;
}

void HerbForm::on_closeButton_clicked()
{
    reject();
}


void HerbForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must not be empty");
        return;
    }

    HerbModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionTextEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Herb saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Herb not saved");
    }
}

