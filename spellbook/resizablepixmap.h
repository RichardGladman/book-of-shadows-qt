#ifndef RESIZABLEPIXMAP_H
#define RESIZABLEPIXMAP_H

#include <QGraphicsRectItem>
#include "renderhandles.h"

class ResizablePixmap: public QGraphicsRectItem, public RenderHandles
{
public:
    explicit ResizablePixmap(QPixmap pixmap, QString glyph);

    QRectF selectorFrameBounds() const override;
    void selectorFrameBounds(QRectF boundsRect) override;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPixmap pixmap() const;
    void pixmap(const QPixmap &value);

    QString glyph() const;

private:
    QPixmap mPixmap;
    QString m_glyph;
};

#endif // RESIZABLEPIXMAP_H
