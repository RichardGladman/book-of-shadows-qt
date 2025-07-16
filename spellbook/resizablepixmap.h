#ifndef RESIZABLEPIXMAP_H
#define RESIZABLEPIXMAP_H

#include <QGraphicsRectItem>
#include "renderhandles.h"

class ResizablePixmap: public QGraphicsRectItem, public RenderHandles
{
public:
    explicit ResizablePixmap(QPixmap pixmap);

    QRectF selectorFrameBounds() const override;
    void selectorFrameBounds(QRectF boundsRect) override;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, QStyleOptionGraphicsItem *option, QWidget *widget);

    QPixmap pixmap() const;
    void pixmap(const QPixmap &value);

private:
    QPixmap mPixmap;
};

#endif // RESIZABLEPIXMAP_H
