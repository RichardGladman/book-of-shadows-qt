#ifndef HANDLES_H
#define HANDLES_H

#include <QRectF>
#include <QPainter>
#include <QGraphicsItem>
#include "handle.h"

class RenderHandles
{
public:
    RenderHandles() = default;
    virtual ~RenderHandles() = default;

    virtual QRectF selectorFrameBounds() const = 0;
    virtual void setSelectorFrameBounds(const QRectF bounsRect) = 0;

    void drawHandlesIfNecessary();
    void setOwner(QGraphicsItem *item);

private:
    QList<Handle *> handles;
    QGraphicsItem *owner;
    bool handlesAdded;

    void drawHandles();
};

#endif // HANDLES_H
