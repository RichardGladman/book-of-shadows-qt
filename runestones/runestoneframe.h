#ifndef RUNESTONEFRAME_H
#define RUNESTONEFRAME_H

#include <QFrame>

namespace Ui {
class RunestoneFrame;
}

class RunestoneFrame : public QFrame
{
    Q_OBJECT

public:
    explicit RunestoneFrame(QWidget *parent = nullptr);
    ~RunestoneFrame();

private slots:
    void on_searchButton_clicked();
    void on_viewButton_clicked();
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::RunestoneFrame *ui;

    void loadData();
};

#endif // RUNESTONEFRAME_H
