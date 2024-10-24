#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "polarity/polarityframe.h"
#include "settings/settingsframe.h"
#include "colours/coloursframe.h"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QSettings>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

extern int version_major;
extern int version_minor;
extern int version_patch;

QString baseDir;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSettings settings("TheFifthContinent", "BookOfShadows");

    settings.beginGroup("Paths");
    baseDir = settings.value("datadir").toString();
    settings.endGroup();

    if (baseDir.isEmpty()) {
        on_actionSettinga_triggered();
        QMessageBox::information(this, "Action Required", "Please select a data directory and restart");
        return;
    }

    createDataStore(baseDir);

    QSqlDatabase dbConnection = QSqlDatabase::addDatabase("QSQLITE");
    dbConnection.setDatabaseName(baseDir + "/data/bos.db");

    if (!dbConnection.open()) {
        qDebug() << "Database connection error";
    } else {
        qDebug() << "Database connection success";
    }

    createDatabaseTables(baseDir);

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

void MainWindow::on_actionColours_triggered()
{
    ColoursFrame *coloursFrame = new ColoursFrame(this);
    setCentralWidget(coloursFrame);
}

void MainWindow::createDataStore(const QString &base)
{
    QDir dir(base + "/data");
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::critical(this, "Error", "Failed to create data directory");
            return;
        }
    }

    dir = QDir(base + "/images");
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::critical(this, "Error", "Failed to create images directory");
            return;
        }
    }

    QFile file(base + "/data/bos.db");
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }
}

void MainWindow::createDatabaseTables(const QString &base)
{
    if (version_major == 0 && version_minor == 1) {
        QString sql = "CREATE TABLE IF NOT EXISTS polarities (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT, image VARCHAR(255));";
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
    }
}

