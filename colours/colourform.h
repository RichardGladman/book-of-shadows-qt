#ifndef COLOURFORM_H
#define COLOURFORM_H

#include <QDialog>

namespace Ui {
class ColourForm;
}

class ColourForm : public QDialog
{
    Q_OBJECT

public:
    explicit ColourForm(QWidget *parent = nullptr, int id = 0);
    ~ColourForm();

private slots:
    void on_closeButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::ColourForm *ui;

    int m_id {};
};

#endif // COLOURFORM_H
