#ifndef POLARITYFRAME_H
#define POLARITYFRAME_H

#include <QFrame>

namespace Ui {
class PolarityFrame;
}

class PolarityFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PolarityFrame(QWidget *parent = nullptr);
    ~PolarityFrame();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_viewButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::PolarityFrame *ui;

    void loadData();
};

#endif // POLARITYFRAME_H
