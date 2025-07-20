#ifndef RUNESPELLFORM_H
#define RUNESPELLFORM_H

#include <QGraphicsScene>
#include <QDialog>

namespace Ui {
class RuneSpellForm;
}

class RuneSpellForm : public QDialog
{
    Q_OBJECT

public:
    explicit RuneSpellForm(QWidget *parent = nullptr);
    ~RuneSpellForm();

private slots:
    void on_fehuButton_clicked();

private:
    Ui::RuneSpellForm *ui;
    QGraphicsScene *scene;
};

#endif // RUNESPELLFORM_H
