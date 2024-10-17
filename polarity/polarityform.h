#ifndef POLARITYFORM_H
#define POLARITYFORM_H

#include <QDialog>

namespace Ui {
class PolarityForm;
}

class PolarityForm : public QDialog
{
    Q_OBJECT

public:
    explicit PolarityForm(QWidget *parent = nullptr);
    ~PolarityForm();

private slots:
    void on_selectButton_clicked();

    void on_saveButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PolarityForm *ui;
};

#endif // POLARITYFORM_H
