#include "treeform.h"
#include "ui_treeform.h"

#include "treemodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

TreeForm::TreeForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::TreeForm), m_default_name {}, m_default_description {}
{
    ui->setupUi(this);

    if (id != 0) {
        TreeModel model = TreeModel::load(id);
        ui->nameLinedit->setText(model.name());
        ui->descriptionTexrEdit->setPlainText(model.description());
        m_id = id;
        m_default_name = model.name();
        m_default_description = model.description();
    }

    if (mode == "view") {
        ui->nameLinedit->setEnabled(false);
        ui->descriptionTexrEdit->setEnabled(false);
        ui->saveButton->setVisible(false);
        ui->saveButton->setEnabled(false);
    }
}

TreeForm::~TreeForm()
{
    delete ui;
}

void TreeForm::on_saveButton_clicked()
{
    QString name = ui->nameLinedit->text();
    QString description = ui->descriptionTexrEdit->toPlainText();


    if (name.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    TreeModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLinedit->clear();
            ui->descriptionTexrEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), tr("Colour saved"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Colour not saved"));
    }

}


void TreeForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (m_default_name != ui->nameLinedit->text() ||
                                     m_default_description != ui->descriptionTexrEdit->toPlainText())) {
        int button = QMessageBox::warning(this, tr("Unsaved Changes"),
            tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
                                          QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }

    reject();
}

