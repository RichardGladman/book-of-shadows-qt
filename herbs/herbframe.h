#ifndef HERBFRAME_H
#define HERBFRAME_H

#include <QFrame>

namespace Ui {
class HerbFrame;
}

class HerbFrame : public QFrame
{
    Q_OBJECT

public:
    explicit HerbFrame(QWidget *parent = nullptr);
    ~HerbFrame();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_viewButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::HerbFrame *ui;

    void loadData();
};

#endif // HERBFRAME_H
