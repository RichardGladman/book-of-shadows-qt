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

    void on_search_button_clicked();

    void on_planetsTableView_doubleClicked(const QModelIndex &index);

private:
    Ui::PlanetsFrame *ui;

    QString m_search_for;

    void loadData();
};

#endif // PLANETSFRAME_H
