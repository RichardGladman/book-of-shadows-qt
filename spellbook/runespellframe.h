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

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_viewButton_clicked();

private:
    Ui::RuneSpellFrame *ui;

    void loadData();
};

#endif // RUNESPELLFRAME_H
