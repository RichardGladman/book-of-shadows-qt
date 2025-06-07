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

#include "dbinitializer.h"

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

    DBInitializer *init = new DBInitializer();

    init->createDataStore(baseDir);

    QSqlDatabase dbConnection = QSqlDatabase::addDatabase("QSQLITE");
    dbConnection.setDatabaseName(baseDir + "/data/bos.db");

    if (!dbConnection.open()) {
        qDebug() << "Database connection error";
    } else {
        qDebug() << "Database connection success";
    }

    init->createDatabaseTables();

    delete init;

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

