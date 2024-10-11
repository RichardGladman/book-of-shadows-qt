#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "polarity/polarityframe.h"
#include "settings/settingsframe.h"

#include <QSettings>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSettings settings("TheFifthContinent", "BookOfShadows");

    settings.beginGroup("Paths");
    QString dataDir = settings.value("datadir").toString();
    settings.endGroup();

    if (dataDir.isEmpty()) {
        on_actionSettinga_triggered();
        QMessageBox::information(this, "Action Required", "Please select a data directory and restart");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPolarity_triggered()
{
    PolarityFrame *polarityFrame = new PolarityFrame(this);
    setCentralWidget(polarityFrame);
}


void MainWindow::on_actionSettinga_triggered()
{
    SettingsFrame *settingsFrame = new SettingsFrame(this);
    setCentralWidget(settingsFrame);
}

