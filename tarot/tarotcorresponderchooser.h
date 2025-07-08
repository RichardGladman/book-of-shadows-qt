#ifndef TAROTCORRESPONDERCHOOSER_H
#define TAROTCORRESPONDERCHOOSER_H


#include <QDialog>
#include <string>

#include "tarotform.h"

namespace Ui {
class TarotCorresponderChooser;
}

class TarotCorresponderChooser : public QDialog
{
    Q_OBJECT

public:
    explicit TarotCorresponderChooser(TarotForm *parent = nullptr, std::string corresponder = "God");
    ~TarotCorresponderChooser();

private slots:
    void on_closeButton_clicked();

    void on_addButton_clicked();

private:
    Ui::TarotCorresponderChooser *ui;

    std::string m_corresponder;
    TarotForm *m_parent;
};

#endif // TAROTCORRESPONDERCHOOSER_H
