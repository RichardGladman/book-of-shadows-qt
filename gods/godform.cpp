#include "godform.h"
#include "ui_godform.h"

#include "godmodel.h"
#include "../polarity/polaritymodel.h"

#include <QMessageBox>
#include <QSqlQuery>

GodForm::GodForm(QWidget *parent, int id)
    : QDialog(parent)
    , ui(new Ui::GodForm)
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
    }
}

GodForm::~GodForm()
{
    delete ui;
}

void GodForm::on_closeButton_clicked()
{
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

