#ifndef RUNESTONEFORM_H
#define RUNESTONEFORM_H

#include <QDialog>

namespace Ui {
class RunestoneForm;
}

class RunestoneForm : public QDialog
{
    Q_OBJECT

public:
    explicit RunestoneForm(QWidget *parent = nullptr);
    ~RunestoneForm();

private:
    Ui::RunestoneForm *ui;
};

#endif // RUNESTONEFORM_H
