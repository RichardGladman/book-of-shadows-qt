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

    enum {Type = UserType + 2 };

    explicit Handle(Position position);

    int type() const override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Position handlePosition;
};

#endif // HANDLE_H
