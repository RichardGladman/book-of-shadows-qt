#ifndef INGREDIENTSFORM_H
#define INGREDIENTSFORM_H

#include <QDialog>

namespace Ui {
class IngredientsForm;
}

class IngredientsForm : public QDialog
{
    Q_OBJECT

public:
    explicit IngredientsForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~IngredientsForm();

private slots:
    void on_saveButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::IngredientsForm *ui;

    int m_id {};

    QString m_default_name;
    QString m_default_description;
};

#endif // INGREDIENTSFORM_H
