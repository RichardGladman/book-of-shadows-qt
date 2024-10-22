#ifndef COLOURSFRAME_H
#define COLOURSFRAME_H

#include <QFrame>

namespace Ui {
class ColoursFrame;
}

class ColoursFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ColoursFrame(QWidget *parent = nullptr);
    ~ColoursFrame();

private:
    Ui::ColoursFrame *ui;
};

#endif // COLOURSFRAME_H
