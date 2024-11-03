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

private:
    Ui::HerbFrame *ui;
};

#endif // HERBFRAME_H
