#ifndef HERBFORM_H
#define HERBFORM_H

#include <QDialog>

namespace Ui {
class HerbForm;
}

class HerbForm : public QDialog
{
    Q_OBJECT

public:
    explicit HerbForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~HerbForm();

private slots:
    void on_closeButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::HerbForm *ui;

    int m_id {};

    QString m_default_name;
    QString m_default_description;
};

#endif // HERBFORM_H
