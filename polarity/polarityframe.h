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

private:
    Ui::PolarityFrame *ui;
};

#endif // POLARITYFRAME_H
