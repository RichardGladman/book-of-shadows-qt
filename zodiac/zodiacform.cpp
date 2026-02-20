#include "zodiacform.h"
#include "ui_zodiacform.h"

#include "zodiacmodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

ZodiacForm::ZodiacForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::ZodiacForm), m_default_name {}, m_default_description {}
{
    ui->setupUi(this);

    if (id != 0) {
        ZodiacModel model = ZodiacModel::load(id);
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

ZodiacForm::~ZodiacForm()
{
    delete ui;
}

void ZodiacForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();

    if (name.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    ZodiacModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionTextEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), tr("Zodiac saved"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Zodiac not saved"));
    }
}


void ZodiacForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (m_default_name != ui->nameLineEdit->text() ||
                                     m_default_description != ui->descriptionTextEdit->toPlainText())) {
        int button = QMessageBox::warning(this, tr("Unsaved Changes"),
                tr("You have unsaved changes, if you continue they will be lost. Do you want to continue"),
                                          QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No) {
            return;
        }
    }

    reject();
}

