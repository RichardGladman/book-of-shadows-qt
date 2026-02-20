#ifndef TREESFRAME_H
#define TREESFRAME_H

#include <QFrame>

namespace Ui {
class TreesFrame;
}

class TreesFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TreesFrame(QWidget *parent = nullptr);
    ~TreesFrame();

private slots:
    void on_viewButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

    void on_search_button_clicked();

    void on_treesTable_doubleClicked(const QModelIndex &index);

private:
    Ui::TreesFrame *ui;

    QString m_search_for;

    void loadData();
};

#endif // TREESFRAME_H
