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
    explicit GodForm(QWidget *parent = nullptr);
    ~GodForm();

private slots:
    void on_closeButton_clicked();

private:
    Ui::GodForm *ui;
};

#endif // GODFORM_H
