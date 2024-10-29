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

private:
    Ui::GodFrame *ui;
};

#endif // GODFRAME_H
