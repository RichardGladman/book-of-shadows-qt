#include "herbform.h"
#include "ui_herbform.h"

#include "herbmodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

HerbForm::HerbForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::HerbForm), m_default_name {""}, m_default_description {""}
{
    ui->setupUi(this);

    if (id != 0) {
        HerbModel model = HerbModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->descriptionTextEdit->setText(model.description());

        m_id = id;
        m_default_name = model.name();
        m_default_description = model.description();
    }

    if (mode == "view") {
        ui->nameLineEdit->setEnabled(false);
        ui->descriptionTextEdit->setEnabled(false);
        ui->saveButton->setEnabled(false);
        ui->saveButton->setVisible(false);
    }
}

HerbForm::~HerbForm()
{
    delete ui;
}

void HerbForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (ui->nameLineEdit->text() != m_default_name ||
                                     ui->descriptionTextEdit->toPlainText() != m_default_description)) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Unsaved Changes",
            "You have unsaved changes. If you continue they will be lost, do you want to continue?",
                                                                  QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }

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

