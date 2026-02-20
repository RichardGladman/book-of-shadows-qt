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

    void on_searchButton_clicked();

    void on_spellTableView_doubleClicked(const QModelIndex &index);

private:
    Ui::RuneSpellFrame *ui;

    void loadData();

    QString m_search_for;
};

#endif // RUNESPELLFRAME_H
