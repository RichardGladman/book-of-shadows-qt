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
#include "notes/notesframe.h"
#include "runestones/runestoneframe.h"
#include "tarot/tarotframe.h"
#include "crystals/crystalframe.h"
#include "spellbook/runespellframe.h"
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
    setWindowTitle("Book of Shadows:- Polarity");
    setCentralWidget(polarityFrame);
}


void MainWindow::on_actionSettinga_triggered()
{
    SettingsFrame *settingsFrame = new SettingsFrame(this);
    setWindowTitle("Book of Shadows:- Settings");
    setCentralWidget(settingsFrame);
}

void MainWindow::on_actionColours_triggered()
{
    ColourFrame *coloursFrame = new ColourFrame(this);
    setWindowTitle("Book of Shadows:- Colours");
    setCentralWidget(coloursFrame);
}

void MainWindow::on_actionGods_triggered()
{
    GodFrame *godFrame = new GodFrame(this);
    setWindowTitle("Book of Shadows:- Gods");
    setCentralWidget(godFrame);
}

void MainWindow::on_actionHerbs_triggered()
{
    HerbFrame *herbFrame = new HerbFrame(this);
    setWindowTitle("Book of Shadows:- Herbs");
    setCentralWidget(herbFrame);
}

void MainWindow::on_actionPlanets_triggered()
{
    PlanetsFrame *planetsFrame = new PlanetsFrame(this);
    setWindowTitle("Book of Shadows:- Planets");
    setCentralWidget(planetsFrame);
}

void MainWindow::on_actionAnimals_triggered()
{
    AnimalFrame *animalFrame = new AnimalFrame(this);
    setWindowTitle("Book of Shadows:- Animals");
    setCentralWidget(animalFrame);
}

void MainWindow::on_actionTrees_triggered()
{
    TreesFrame *treeFrame = new TreesFrame(this);
    setWindowTitle("Book of Shadows:- Trees");
    setCentralWidget(treeFrame);
}

void MainWindow::on_actionZodiac_triggered()
{
    ZodiacFrame *frame = new ZodiacFrame(this);
    setWindowTitle("Book of Shadows:- Zodiac");
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


void MainWindow::on_actionRunestones_triggered()
{
    RunestoneFrame *frame = new RunestoneFrame(this);
    setWindowTitle("Book of Shadows:- Runes");
    setCentralWidget(frame);
}

void MainWindow::on_actionCrystals_triggered()
{
    CrystalFrame *frame = new CrystalFrame(this);
    setWindowTitle("Book of Shadows:- Crystals");
    setCentralWidget(frame);
}


void MainWindow::on_actionTarot_Cards_triggered()
{
    TarotFrame *frame = new TarotFrame(this);
    setWindowTitle("Book of Shadows:- Tarot Cards");
    setCentralWidget(frame);
}


void MainWindow::on_actionNotes_triggered()
{
    NotesFrame *frame = new NotesFrame(this);
    setWindowTitle("Book of Shadows:- Notes");
    setCentralWidget(frame);
}


void MainWindow::on_actionRunes_triggered()
{
    RuneSpellFrame *frame = new RuneSpellFrame(this);
    setWindowTitle("Book of Shadows:- Rune Spells");
    setCentralWidget(frame);
}

