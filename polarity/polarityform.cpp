#include "polarityform.h"
#include "ui_polarityform.h"

#include "polaritymodel.h"
#include "../settings/settingsmodel.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

extern SettingsModel settings;

PolarityForm::PolarityForm(QWidget *parent, int id)
    : QDialog(parent)
    , ui(new Ui::PolarityForm), m_default_name {}, m_default_meaning {}, m_default_image {}
{
    ui->setupUi(this);

    if (id != 0) {
        PolarityModel model = PolarityModel::load(id);
        ui->nameLineEdit->setText(model.name());
        ui->descriptionTextEdit->setPlainText(model.meaning());
        ui->imageLineEdit->setText(model.image());

        m_id = id;

        m_default_name = model.name();
        m_default_meaning = model.meaning();
        m_default_image = model.image();
    }
}

PolarityForm::~PolarityForm()
{
    delete ui;
}

void PolarityForm::on_selectButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose image file");
    if (!fileName.isEmpty()) {
        ui->imageLineEdit->setText(fileName);
    }
}

void PolarityForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString meaning = ui->descriptionTextEdit->toPlainText();
    QString image = ui->imageLineEdit->text();

    QString finalImage;

    if (image.contains(settings.data_directory())) {
        finalImage = image;
    } else {
        QList<QString> parts = image.split("/");
        QString filename = parts[parts.length() - 1];
        finalImage = settings.data_directory() + "/images/" + filename;

        QFile file(image);
        file.copy(finalImage);
    }

    PolarityModel model {m_id, name, meaning, finalImage};

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must not be empty.");
        return;
    }

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionTextEdit->clear();
            ui->imageLineEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Polarity saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Polarity not saved");
    }
}


void PolarityForm::on_closeButton_clicked()
{
    if (settings.show_warnings() && (m_default_name != ui->nameLineEdit->text() ||
                                     m_default_meaning != ui->descriptionTextEdit->toPlainText() ||
                                     m_default_image != ui->imageLineEdit->text())) {
        int button = QMessageBox::warning(this, "Unsaved Changes",
                                                                  "You have unsaved changes, if you continue they will be lost. Do you want to continue?",
                                                                  QMessageBox::Yes, QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }

    reject();
}

