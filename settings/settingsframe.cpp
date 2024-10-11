#include "settingsframe.h"
#include "ui_settingsframe.h"

#include <QFileDialog>

SettingsFrame::SettingsFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::SettingsFrame)
{
    ui->setupUi(this);
}

SettingsFrame::~SettingsFrame()
{
    delete ui;
}

void SettingsFrame::on_directoryButton_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, "Choose data directory", QString(), QFileDialog::ShowDirsOnly);
    if (dirName != "") {
        ui->directoryLineEdit->setText(dirName);
    }
}


void SettingsFrame::on_saveButton_clicked()
{

}

