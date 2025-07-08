#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionPolarity_triggered();

    void on_actionSettinga_triggered();

    void on_actionColours_triggered();

    void on_actionGods_triggered();

    void on_actionHerbs_triggered();

    void on_actionPlanets_triggered();

    void on_actionAnimals_triggered();

    void on_actionTrees_triggered();

    void on_actionZodiac_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionAbout_triggered();

    void on_actionRunestones_triggered();

    void on_actionTarot_Cards_triggered();

    void on_actionCrystals_triggered();

    void on_actionNotes_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
