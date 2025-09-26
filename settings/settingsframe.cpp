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
}

SettingsFrame::~SettingsFrame()
{
    delete ui;
}

void SettingsFrame::on_directoryButton_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, "Choose data directory", QString(), QFileDialog::ShowDirsOnly);
    if (!dirName.isEmpty()) {
        ui->directoryLineEdit->setText(dirName);
    }
}


void SettingsFrame::on_saveButton_clicked()
{
    settings.data_directory() = ui->directoryLineEdit->text();

    if (settings.data_directory().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "You must choose a directory");
        return;
    }

    settings.save();
}
