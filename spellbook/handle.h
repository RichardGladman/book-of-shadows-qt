#ifndef HANDLE_H
#define HANDLE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Handle : public QGraphicsRectItem
{
public:

    enum Position
    {
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    explicit Handle(Position position);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Position handlePosition;
};

#endif // HANDLE_H
