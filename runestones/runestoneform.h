#ifndef RUNESTONEFORM_H
#define RUNESTONEFORM_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class RunestoneForm;
}

class RunestoneForm : public QDialog
{
    Q_OBJECT

public:
    explicit RunestoneForm(QWidget *parent = nullptr);
    ~RunestoneForm();

    QListWidget* getListView(std::string view);

private slots:
    void on_addAnimalButton_clicked();

    void on_addColourButton_clicked();

    void on_addGodButton_clicked();

    void on_Herb_clicked();

    void on_addTreeButton_clicked();

    void on_removeTreeButton_clicked();

    void on_removeHerbButton_clicked();

    void on_removeGodButton_clicked();

    void on_removeColourButton_clicked();

    void on_removeAnimalButton_clicked();

private:
    Ui::RunestoneForm *ui;
};

#endif // RUNESTONEFORM_H
