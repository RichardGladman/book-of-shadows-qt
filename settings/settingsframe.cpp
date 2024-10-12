#include "settingsframe.h"
#include "ui_settingsframe.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

SettingsFrame::SettingsFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::SettingsFrame)
{
    ui->setupUi(this);

    QSettings settings("TheFifthContinent", "BookOfShadows");

    settings.beginGroup("Paths");
    ui->directoryLineEdit->setText(settings.value("datadir").toString());
    settings.endGroup();
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
    QString dirName = ui->directoryLineEdit->text();

    if (dirName.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "You must choose a directory");
        return;
    }

    QSettings settings("TheFifthContinent", "BookOfShadows");

    settings.beginGroup("Paths");
    settings.setValue("datadir", dirName);
    settings.endGroup();
}
