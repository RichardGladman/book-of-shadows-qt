#ifndef ANIMALFORM_H
#define ANIMALFORM_H

#include <QDialog>

namespace Ui {
class AnimalForm;
}

class AnimalForm : public QDialog
{
    Q_OBJECT

public:
    explicit AnimalForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~AnimalForm();

private slots:
    void on_saveButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::AnimalForm *ui;

    QString m_default_name;
    QString m_default_description;

    int m_id {};
};

#endif // ANIMALFORM_H
