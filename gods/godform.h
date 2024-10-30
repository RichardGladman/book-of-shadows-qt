#ifndef GODFORM_H
#define GODFORM_H

#include <QDialog>

namespace Ui {
class GodForm;
}

class GodForm : public QDialog
{
    Q_OBJECT

public:
    explicit GodForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~GodForm();

private slots:
    void on_closeButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::GodForm *ui;

    int m_id {};
};

#endif // GODFORM_H
