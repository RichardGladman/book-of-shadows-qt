#ifndef RUNESPELLFRAME_H
#define RUNESPELLFRAME_H

#include <QFrame>

namespace Ui {
class RuneSpellFrame;
}

class RuneSpellFrame : public QFrame
{
    Q_OBJECT

public:
    explicit RuneSpellFrame(QWidget *parent = nullptr);
    ~RuneSpellFrame();

private slots:
    void on_addButton_clicked();

private:
    Ui::RuneSpellFrame *ui;
};

#endif // RUNESPELLFRAME_H
