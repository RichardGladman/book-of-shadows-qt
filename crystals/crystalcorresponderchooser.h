#ifndef CRYSTALCORRESPONDERCHOOSER_H
#define CRYSTALCORRESPONDERCHOOSER_H


#include <QDialog>
#include <string>

#include "crystalform.h"

namespace Ui {
class CrystalCorresponderChooser;
}

class CrystalCorresponderChooser : public QDialog
{
    Q_OBJECT

public:
    explicit CrystalCorresponderChooser(CrystalForm *parent = nullptr, std::string corresponder = "God");
    ~CrystalCorresponderChooser();

private slots:
    void on_closeButton_clicked();

    void on_addButton_clicked();

private:
    Ui::CrystalCorresponderChooser *ui;

    std::string m_corresponder;
    CrystalForm *m_parent;
};

#endif // CRYSTALCORRESPONDERCHOOSER_H
