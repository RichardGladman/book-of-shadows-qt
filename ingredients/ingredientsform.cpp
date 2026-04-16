#include "ingredientsform.h"
#include "ui_ingredientsform.h"

#include "ingredientmodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

IngredientsForm::IngredientsForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::IngredientsForm), m_default_name {}, m_default_description {}
{
    ui->setupUi(this);

    if (id != 0) {
        IngredientModel model = IngredientModel::load(id);
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

IngredientsForm::~IngredientsForm()
{
    delete ui;
}

void IngredientsForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->meaningTextEdit->toPlainText();

    if (name.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    IngredientModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->meaningTextEdit->clear();
            ui->nameLineEdit->focusWidget();
        } else {
            QMessageBox::information(this, tr("Success"), tr("Ingredient saved"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Ingredient not saved"));
    }
}


void IngredientsForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (m_default_name != ui->nameLineEdit->text() ||
                                     m_default_description != ui->meaningTextEdit->toPlainText())) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
            tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No) {
            return;
        }
	    reject();
    }
}

