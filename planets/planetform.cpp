#include "planetform.h"
#include "ui_planetform.h"

#include "planetmodel.h"

#include <QMessageBox>

PlanetForm::PlanetForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::PlanetForm)
{
    ui->setupUi(this);

    if (id != 0) {
        PlanetModel model = PlanetModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->meaningTextEdit->setPlainText(model.description());

        m_id = id;
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
    reject();
}

