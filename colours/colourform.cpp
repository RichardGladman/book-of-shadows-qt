#include "colourform.h"
#include "ui_colourform.h"

#include "colourmodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

ColourForm::ColourForm(QWidget *parent, int id, QString mode)
    : QDialog(parent), m_default_name {""}, m_default_description {""}
    , ui(new Ui::ColourForm)
{
    ui->setupUi(this);

    if (id != 0) {
        ColourModel model = ColourModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->meaningTextEdit->setPlainText(model.meaning());

        m_id = id;
    }

    if (mode == "view") {
        ui->nameLineEdit->setEnabled(false);
        ui->meaningTextEdit->setEnabled(false);
        ui->saveButton->setVisible(false);
        ui->saveButton->setEnabled(false);
    }
}

ColourForm::~ColourForm()
{
    delete ui;
}

void ColourForm::on_closeButton_clicked()
{
    if (settings.show_warnings() &&
        (m_default_name != ui->nameLineEdit->text() || m_default_description != ui->meaningTextEdit->toPlainText())) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Unsaved Changes",
            "You have unsaved changes. If you continue they will be lost, do you want to continue?",
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }

    reject();
}


void ColourForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString meaning = ui->meaningTextEdit->toPlainText();

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must not be empty");
        return;
    }

    ColourModel model {m_id, name, meaning};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->meaningTextEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Colour saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Colour not saved");
    }
}

