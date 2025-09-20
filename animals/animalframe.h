#ifndef ANIMALFRAME_H
#define ANIMALFRAME_H

#include <QFrame>

namespace Ui {
class AnimalFrame;
}

class AnimalFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AnimalFrame(QWidget *parent = nullptr);
    ~AnimalFrame();

private slots:
    void on_viewButton_clicked();

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_searchPushButton_clicked();

private:
    Ui::AnimalFrame *ui;

    QString m_search_for;

    void loadData();
};

#endif // ANIMALFRAME_H
