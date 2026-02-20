#include "settingsframe.h"
#include "ui_settingsframe.h"

#include <QFileDialog>
#include <QMessageBox>

#include "settingsmodel.h"

extern SettingsModel settings;

SettingsFrame::SettingsFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::SettingsFrame)
{
    ui->setupUi(this);

    ui->directoryLineEdit->setText(settings.data_directory());
    ui->warnings_checkbox->setChecked(settings.show_warnings());
}

SettingsFrame::~SettingsFrame()
{
    delete ui;
}

void SettingsFrame::on_directoryButton_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Choose data directory"), QString(), QFileDialog::ShowDirsOnly);
    if (!dirName.isEmpty()) {
        ui->directoryLineEdit->setText(dirName);
    }
}


void SettingsFrame::on_saveButton_clicked()
{
    settings.data_directory(ui->directoryLineEdit->text());
    settings.show_warnings(ui->warnings_checkbox->isChecked());

    if (settings.data_directory().isEmpty()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("You must choose a directory"));
        return;
    }

    settings.save();
}
