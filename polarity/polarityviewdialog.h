#ifndef POLARITYVIEWDIALOG_H
#define POLARITYVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class PolarityViewDialog;
}

class PolarityViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PolarityViewDialog(QWidget *parent = nullptr, int id=0);
    ~PolarityViewDialog();

private slots:
    void on_closeButton_clicked();

private:
    Ui::PolarityViewDialog *ui;
};

#endif // POLARITYVIEWDIALOG_H
