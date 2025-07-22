#include "renderhandles.h"

#include <QGraphicsScene>
#include <QDebug>

void RenderHandles::drawHandlesIfNecessary()
{
    if (!owner) {
        qWarning() << "RenderHandles: No owner set";
        return;
    }

    if (owner->isSelected()) {
        drawHandles();
        handlesAdded = true;
    } else {
        foreach (Handle *handle, handles) {
            owner->scene()->removeItem(handle);
        }

        qDeleteAll(handles);
        handles.clear();
        handlesAdded = false;
    }
}

void RenderHandles::setOwner(QGraphicsItem *item)
{
    owner = item;
}

void RenderHandles::drawHandles()
{
    if (handles.count() == 0) {
        handles.append(new Handle(Handle::TOP_LEFT));
        handles.append(new Handle(Handle::TOP_RIGHT));
        handles.append(new Handle(Handle::BOTTOM_RIGHT));
        handles.append(new Handle(Handle::BOTTOM_LEFT));
    }

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);

    QPointF corner = selectorFrameBounds().topLeft() + QPointF(-12, -12);
    handles[0]->setRect(QRectF(corner, QSize(12, 12)));
    if (!handles.isEmpty() && !handlesAdded) {
        handles[0]->setPen(pen);
        handles[0]->setBrush(Qt::gray);
        owner->scene()->addItem(handles[0]);
        handles[0]->setParentItem(owner);
    }

    corner = selectorFrameBounds().topRight() + QPointF(0, -12);
    handles[1]->setRect(QRectF(corner, QSize(12, 12)));
    if (!handles.isEmpty() && !handlesAdded) {
        handles[1]->setPen(pen);
        handles[1]->setBrush(Qt::gray);
        owner->scene()->addItem(handles[1]);
        handles[1]->setParentItem(owner);
    }

    corner = selectorFrameBounds().bottomRight() + QPointF(0, 0);
    handles[2]->setRect(QRectF(corner, QSize(12, 12)));
    if (!handles.isEmpty() && !handlesAdded) {
        handles[2]->setPen(pen);
        handles[2]->setBrush(Qt::gray);
        owner->scene()->addItem(handles[2]);
        handles[2]->setParentItem(owner);
    }

    corner = selectorFrameBounds().bottomLeft() + QPointF(-12, 0);
    handles[3]->setRect(QRectF(corner, QSize(12, 12)));
    if (!handles.isEmpty() && !handlesAdded) {
        handles[3]->setPen(pen);
        handles[3]->setBrush(Qt::gray);
        owner->scene()->addItem(handles[3]);
        handles[3]->setParentItem(owner);
    }
}
