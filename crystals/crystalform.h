#ifndef CRYSTALFORM_H
#define CRYSTALFORM_H

#include <QDialog>
#include <QListWidget>

#include "crystalmodel.h"

namespace Ui {
class CrystalForm;
}

class CrystalForm : public QDialog
{
    Q_OBJECT

public:
    explicit CrystalForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~CrystalForm();

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

    void on_closeButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::CrystalForm *ui;

    int m_id {};

    void saveCorresponders(CrystalModel model);
};

#endif // CRYSTALFORM_H
