#include "animalform.h"
#include "ui_animalform.h"

#include "animalmodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

AnimalForm::AnimalForm(QWidget *parent, int id, QString mode)
    : QDialog(parent), m_default_name {""}, m_default_description {""}
    , ui(new Ui::AnimalForm)
{
    ui->setupUi(this);

    if (id != 0) {
        AnimalModel model = AnimalModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->descriptionTextEdit->setPlainText(model.description());
        m_id = id;
        m_default_name = model.name();
        m_default_description = model.description();
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
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    AnimalModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionTextEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), tr("Animal saved"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Animal not saved"));
    }
}


void AnimalForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (ui->nameLineEdit->text() != m_default_name ||
                                         ui->descriptionTextEdit->toPlainText() != m_default_description)) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
                             tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
                                QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}

