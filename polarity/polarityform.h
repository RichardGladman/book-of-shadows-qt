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
    explicit PolarityForm(QWidget *parent = nullptr, int id = 0);
    ~PolarityForm();

private slots:
    void on_selectButton_clicked();

    void on_saveButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PolarityForm *ui;

    int m_id {0};

    QString m_default_name;
    QString m_default_meaning;
    QString m_default_image;
};

#endif // POLARITYFORM_H
