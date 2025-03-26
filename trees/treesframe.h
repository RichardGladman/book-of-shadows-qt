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

private:
    Ui::TreesFrame *ui;

    void loadData();
};

#endif // TREESFRAME_H
