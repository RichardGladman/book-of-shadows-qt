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

private:
    Ui::HerbForm *ui;
};

#endif // HERBFORM_H
