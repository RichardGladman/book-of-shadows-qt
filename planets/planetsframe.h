#ifndef PLANETSFRAME_H
#define PLANETSFRAME_H

#include <QFrame>

namespace Ui {
class PlanetsFrame;
}

class PlanetsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PlanetsFrame(QWidget *parent = nullptr);
    ~PlanetsFrame();

private:
    Ui::PlanetsFrame *ui;
};

#endif // PLANETSFRAME_H
