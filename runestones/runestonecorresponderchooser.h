#ifndef RUNESTONECORRESPONDERCHOOSER_H
#define RUNESTONECORRESPONDERCHOOSER_H

#include <QDialog>
#include <string>

#include "runestoneform.h"

namespace Ui {
class RunestoneCorresponderChooser;
}

class RunestoneCorresponderChooser : public QDialog
{
    Q_OBJECT

public:
    explicit RunestoneCorresponderChooser(RunestoneForm *parent = nullptr, std::string corresponder = "God");
    ~RunestoneCorresponderChooser();

private slots:
    void on_closeButton_clicked();

    void on_addButton_clicked();

private:
    Ui::RunestoneCorresponderChooser *ui;

    std::string m_corresponder;
    RunestoneForm *m_parent;
};

#endif // RUNESTONECORRESPONDERCHOOSER_H
