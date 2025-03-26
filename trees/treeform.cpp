#include "treeform.h"
#include "ui_treeform.h"

#include "treemodel.h"

#include <QMessageBox>

TreeForm::TreeForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::TreeForm)
{
    ui->setupUi(this);

    if (id != 0) {
        TreeModel model = TreeModel::load(id);
        ui->nameLinedit->setText(model.name());
        ui->descriptionTexrEdit->setPlainText(model.description());
        m_id = id;
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
        QMessageBox::critical(this, "Input Error", "Name must not be empty");
        return;
    }

    TreeModel model {m_id, name, description};

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLinedit->clear();
            ui->descriptionTexrEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Colour saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Colour not saved");
    }

}


void TreeForm::on_closeButton_clicked()
{
    reject();
}

