#include "animalform.h"
#include "ui_animalform.h"

#include "animalmodel.h"

#include <QMessageBox>

AnimalForm::AnimalForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::AnimalForm)
{
    ui->setupUi(this);

    if (id != 0) {
        AnimalModel model = AnimalModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->descriptionTextEdit->setPlainText(model.description());
        m_id = id;
    }

    if (mode == "view") {
        ui->nameLineEdit->setEnabled(false);
        ui->descriptionTextEdit->setEnabled(false);
        ui->saveButton->setVisible(false);
        ui->saveButton->setEnabled(false);
    }
}

AnimalForm::~AnimalForm()
{
    delete ui;
}

void AnimalForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must not be empty");
        return;
    }

    AnimalModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionTextEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Animal saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Animal not saved");
    }
}


void AnimalForm::on_closeButton_clicked()
{
    reject();
}

