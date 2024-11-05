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
    explicit HerbForm(QWidget *parent = nullptr);
    ~HerbForm();

private slots:
    void on_closeButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::HerbForm *ui;

    int m_id {};
};

#endif // HERBFORM_H
