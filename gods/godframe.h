#ifndef GODFRAME_H
#define GODFRAME_H

#include <QFrame>

namespace Ui {
class GodFrame;
}

class GodFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GodFrame(QWidget *parent = nullptr);
    ~GodFrame();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_viewButton_clicked();

    void on_deleteButton_clicked();

    void on_search_button_clicked();

private:
    Ui::GodFrame *ui;

    QString m_search_for;

    void loadData();
};

#endif // GODFRAME_H
