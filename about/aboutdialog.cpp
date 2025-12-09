#include "aboutdialog.h"
#include "ui_aboutdialog.h"

extern int version_major;
extern int version_minor;
extern int version_patch;

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->versionLabel->setText(tr("Version: ") + QString::number(version_major) + "." + QString::number(version_minor) + "." + QString::number(version_patch));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_clicked()
{
    reject();
}

