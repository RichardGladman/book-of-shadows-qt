#include "colourform.h"
#include "ui_colourform.h"

#include "colourmodel.h"

#include <QMessageBox>

ColourForm::ColourForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
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

