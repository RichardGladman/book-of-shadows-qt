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

private:
    Ui::MainWindow *ui;

    void createDataStore(const QString &base);
    void createDatabaseTables();

    void createPolarity();
    void createColours();
    void createGods();
    void createHerbs();
    void createPlanets();
    void createAnimals();
    void createTrees();
};
#endif // MAINWINDOW_H
