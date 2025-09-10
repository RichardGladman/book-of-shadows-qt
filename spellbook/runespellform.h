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

    void on_uruzButton_clicked();

    void on_thurisazButton_clicked();

    void on_ansuzButton_clicked();

    void on_raidoButton_clicked();

    void on_kaunazButton_clicked();

    void on_geboButton_clicked();

    void on_wunjoButton_clicked();

    void on_hagalazButton_clicked();

    void on_nauthizButton_clicked();

    void on_isaButton_clicked();

    void on_jeraButton_clicked();

    void on_eihwazButton_clicked();

    void on_perthoButton_clicked();

    void on_algizButton_clicked();

    void on_sowuloButton_clicked();

    void on_teiwazButton_clicked();

    void on_berkanaButton_clicked();

    void on_ehwazButton_clicked();

    void on_mannazButton_clicked();

    void on_laguzButton_clicked();

    void on_inguzButton_clicked();

    void on_othilaButton_clicked();

    void on_dagazButton_clicked();

    void on_closeButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::RuneSpellForm *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;

    int m_id {};
};

#endif // RUNESPELLFORM_H
