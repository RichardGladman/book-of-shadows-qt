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

private:
    Ui::GodFrame *ui;
};

#endif // GODFRAME_H
