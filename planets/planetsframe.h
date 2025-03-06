#ifndef PLANETSFRAME_H
#define PLANETSFRAME_H

#include <QFrame>

namespace Ui {
class PlanetsFrame;
}

class PlanetsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PlanetsFrame(QWidget *parent = nullptr);
    ~PlanetsFrame();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_viewButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::PlanetsFrame *ui;

    void loadData();
};

#endif // PLANETSFRAME_H
