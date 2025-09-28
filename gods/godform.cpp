#include "godform.h"
#include "ui_godform.h"

#include "godmodel.h"
#include "../polarity/polaritymodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>
#include <QSqlQuery>

extern SettingsModel settings;

GodForm::GodForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::GodForm), m_default_name {""}, m_default_description {""}, m_default_polarity {0}
{
    ui->setupUi(this);

    QSqlQuery query = PolarityModel::list();

    while (query.next()) {
        ui->polarityCombo->addItem(query.value(1).toString(), query.value(0).toInt());
    }

    if (id != 0) {
        GodModel model = GodModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->descriptionTextEdit->setPlainText(model.description());
        ui->polarityCombo->setCurrentIndex(ui->polarityCombo->findData(model.polarityId()));

        m_id = id;
        m_default_name = model.name();
        m_default_description = model.description();
        m_default_polarity = model.polarityId();
    }

    if (mode == "view") {
        ui->nameLineEdit->setEnabled(false);
        ui->descriptionTextEdit->setEnabled(false);
        ui->polarityCombo->setEnabled(false);
        ui->saveButton->setEnabled(false);
        ui->saveButton->setVisible(false);
    }
}

GodForm::~GodForm()
{
    delete ui;
}

void GodForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (m_default_name != ui->nameLineEdit->text() ||
                                     m_default_description != ui->descriptionTextEdit->toPlainText() ||
                                     m_default_polarity != ui->polarityCombo->currentData().toInt())) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Unsaved Changes",
            "You have unsaved changes. If you continue, you will lose them. Do you want to continue?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}


void GodForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();
    int polarityId = ui->polarityCombo->currentData().toInt();

    QString message;

    if (name.isEmpty()) {
        message += "Name must not be empty\n";
    }

    if (polarityId == 0) {
        message += "You must select a polarity";
    }

    if (!message.isEmpty()) {
        QMessageBox::critical(this, "Input Error", message);
        return;
    }

    GodModel model {m_id, name, description, polarityId};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionTextEdit->clear();
            ui->polarityCombo->clear();
        } else {
            QMessageBox::information(this, "Success", "God saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "God not saved");
    }
}

