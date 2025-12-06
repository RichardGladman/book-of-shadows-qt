#ifndef TAROTFORM_H
#define TAROTFORM_H


#include <QDialog>
#include <QListWidget>

#include "tarotmodel.h"

namespace Ui {
class TarotForm;
}

class TarotForm : public QDialog
{
    Q_OBJECT

public:
    explicit TarotForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~TarotForm();

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
    Ui::TarotForm *ui;

    int m_id {};

    int default_polarity;
    int default_planet;
    int default_zodiac;

    QString default_name;
    QString default_description;

    QList<QString> default_animals;
    QList<QString> default_colours;
    QList<QString> default_gods;
    QList<QString> default_herbs;
    QList<QString> default_trees;

    void saveCorresponders(TarotModel model);
};

#endif // TAROTFORM_H
