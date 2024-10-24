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

private:
    Ui::MainWindow *ui;

    void createDataStore(const QString &base);
    void createDatabaseTables(const QString &base);
};
#endif // MAINWINDOW_H
