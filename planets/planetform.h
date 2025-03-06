#ifndef PLANETFORM_H
#define PLANETFORM_H

#include <QDialog>

namespace Ui {
class PlanetForm;
}

class PlanetForm : public QDialog
{
    Q_OBJECT

public:
    explicit PlanetForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~PlanetForm();

private slots:
    void on_saveButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::PlanetForm *ui;

    int m_id {};
};

#endif // PLANETFORM_H
