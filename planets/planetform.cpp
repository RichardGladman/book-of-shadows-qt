#include "planetform.h"
#include "ui_planetform.h"

#include "planetmodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

PlanetForm::PlanetForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::PlanetForm), m_default_name {}, m_default_description {}
{
    ui->setupUi(this);

    if (id != 0) {
        PlanetModel model = PlanetModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->meaningTextEdit->setPlainText(model.description());

        m_id = id;
        m_default_name = model.name();
        m_default_description = model.description();
    }

    if (mode == "view") {
        ui->nameLineEdit->setEnabled(false);
        ui->meaningTextEdit->setEnabled(false);
        ui->saveButton->setVisible(false);
        ui->saveButton->setEnabled(false);
    }
}

PlanetForm::~PlanetForm()
{
    delete ui;
}

void PlanetForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->meaningTextEdit->toPlainText();

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must not be empty");
        return;
    }

    PlanetModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->meaningTextEdit->clear();
            ui->nameLineEdit->focusWidget();
        } else {
            QMessageBox::information(this, "Success", "Planet saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Planet not saved");
    }
}


void PlanetForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (m_default_name != ui->nameLineEdit->text() ||
                                     m_default_description != ui->meaningTextEdit->toPlainText())) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Unsaved Changes",
            "You have unsaved changes, if you continue they will be lost. Do you want to continue?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}

