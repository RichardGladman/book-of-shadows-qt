#include "handle.h"
#include "renderhandles.h"

Handle::Handle(Position position) : handlePosition {position}
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

void Handle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    RenderHandles *rectItem = dynamic_cast<RenderHandles *>(parentItem());
    if (rectItem) {
        QRectF boundingFrame = rectItem->selectorFrameBounds();

        switch (handlePosition) {
        case TOP_LEFT:
            boundingFrame.setTop(event->pos().y() + 6);
            boundingFrame.setLeft(event->pos().x() + 6);
            break;
        case TOP_RIGHT:
            boundingFrame.setTop(event->pos().y() + 6);
            boundingFrame.setRight(event->pos().x() - 6);
            break;
        case BOTTOM_RIGHT:
            boundingFrame.setBottom(event->pos().y() - 6);
            boundingFrame.setRight(event->pos().x() - 6);
            break;
        case BOTTOM_LEFT:
            boundingFrame.setBottom(event->pos().y() - 6);
            boundingFrame.setLeft(event->pos().x() + 6);
            break;
        }

        rectItem->selectorFrameBounds(boundingFrame.normalized());
    }
}
