#ifndef CORRESPONDERCHOOSER_H
#define CORRESPONDERCHOOSER_H

#include <QDialog>
#include <string>

#include "runestoneform.h"

namespace Ui {
class CorresponderChooser;
}

class CorresponderChooser : public QDialog
{
    Q_OBJECT

public:
    explicit CorresponderChooser(RunestoneForm *parent = nullptr, std::string corresponder = "God");
    ~CorresponderChooser();

private slots:
    void on_closeButton_clicked();

    void on_addButton_clicked();

private:
    Ui::CorresponderChooser *ui;

    std::string m_corresponder;
    RunestoneForm *m_parent;
};

#endif // CORRESPONDERCHOOSER_H
