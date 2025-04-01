#include "zodiacform.h"
#include "ui_zodiacform.h"

#include "zodiacmodel.h"

#include <QMessageBox>

ZodiacForm::ZodiacForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::ZodiacForm)
{
    ui->setupUi(this);

    if (id != 0) {
        ZodiacModel model = ZodiacModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->descriptionTextEdit->setPlainText(model.description());
        m_id = id;
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
        QMessageBox::critical(this, "Input Error", "Name must not be empty");
        return;
    }

    ZodiacModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionTextEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Zodiac saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Zodiac not saved");
    }
}


void ZodiacForm::on_closeButton_clicked()
{
    reject();
}

