#include "colourform.h"
#include "ui_colourform.h"

#include "colourmodel.h"

#include <QMessageBox>

ColourForm::ColourForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ColourForm)
{
    ui->setupUi(this);
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

