#include "resizablepixmap.h"
#include <QPen>
#include <QGraphicsScene>
#include <QPainter>

ResizablePixmap::ResizablePixmap(QPixmap pixmap) : mPixmap{pixmap}
{
    setOwner(this);
    setRect(0, 0, pixmap.width(), pixmap.height());
}

QRectF ResizablePixmap::selectorFrameBounds() const
{
    return rect();
}

void ResizablePixmap::selectorFrameBounds(QRectF boundsRect)
{
    prepareGeometryChange();
    setRect(boundsRect);
    update();
}

QRectF ResizablePixmap::boundingRect() const
{
    return selectorFrameBounds();
}

void ResizablePixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->drawPixmap(selectorFrameBounds(), mPixmap, mPixmap.rect());
    drawHandlesIfNecessary();
    painter->restore();
}

QPixmap ResizablePixmap::pixmap() const
{
    return mPixmap;
}

void ResizablePixmap::pixmap(const QPixmap &value)
{
    mPixmap = value;
}
