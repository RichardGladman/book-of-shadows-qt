#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "polarity/polarityframe.h"
#include "settings/settingsframe.h"
#include "animals/animalframe.h"
#include "colours/colourframe.h"
#include "gods/godframe.h"
#include "herbs/herbframe.h"
#include "planets/planetsframe.h"
#include "trees/treesframe.h"
#include "zodiac/zodiacframe.h"
#include "about/aboutdialog.h"
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

    createDatabaseTables();

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
    ColourFrame *coloursFrame = new ColourFrame(this);
    setCentralWidget(coloursFrame);
}

void MainWindow::on_actionGods_triggered()
{
    GodFrame *godFrame = new GodFrame(this);
    setCentralWidget(godFrame);
}

void MainWindow::on_actionHerbs_triggered()
{
    HerbFrame *herbFrame = new HerbFrame(this);
    setCentralWidget(herbFrame);
}

void MainWindow::on_actionPlanets_triggered()
{
    PlanetsFrame *planetsFrame = new PlanetsFrame(this);
    setCentralWidget(planetsFrame);
}

void MainWindow::on_actionAnimals_triggered()
{
    AnimalFrame *animalFrame = new AnimalFrame(this);
    setCentralWidget(animalFrame);
}

void MainWindow::on_actionTrees_triggered()
{
    TreesFrame *treeFrame = new TreesFrame(this);
    setCentralWidget(treeFrame);
}

void MainWindow::on_actionZodiac_triggered()
{
    ZodiacFrame *frame = new ZodiacFrame(this);
    setCentralWidget(frame);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->exec();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
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

void MainWindow::createDatabaseTables()
{
    createPolarity();
    createColours();
    createGods();
    createHerbs();
    createPlanets();
    createAnimals();
    createTrees();
    createZodiac();
}

void MainWindow::createPolarity()
{
    QString sql = "CREATE TABLE IF NOT EXISTS polarities (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT, image VARCHAR(255));";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void MainWindow::createColours()
{
    QString sql = "CREATE TABLE IF NOT EXISTS colours (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void MainWindow::createGods()
{
    QString sql = "CREATE TABLE IF NOT EXISTS gods (id INTEGER PRIMARY KEY, name VARCHAR(255), polarity_id INTEGER, description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void MainWindow::createHerbs()
{
    QString sql = "CREATE TABLE IF NOT EXISTS herbs (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void MainWindow::createPlanets()
{
    QString sql = "CREATE TABLE IF NOT EXISTS planets (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void MainWindow::createAnimals()
{
    QString sql = "CREATE TABLE IF NOT EXISTS animals (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void MainWindow::createTrees()
{
    QString sql = "CREATE TABLE IF NOT EXISTS trees (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void MainWindow::createZodiac()
{
    QString sql = "CREATE TABLE IF NOT EXISTS zodiac (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

