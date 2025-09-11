#ifndef RESIZABLEPIXMAP_H
#define RESIZABLEPIXMAP_H

#include <QGraphicsRectItem>
#include "renderhandles.h"

class ResizablePixmap: public QGraphicsRectItem, public RenderHandles
{
public:
    enum { Type = UserType + 1 };

    explicit ResizablePixmap(int id, QPixmap pixmap, QString glyph);

    QRectF selectorFrameBounds() const override;
    void selectorFrameBounds(QRectF boundsRect) override;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int id();
    void id (int id);

    QPixmap pixmap() const;
    void pixmap(const QPixmap &value);

    QString glyph() const;

    int type() const override;

private:
    int m_id;
    QPixmap mPixmap;
    QString m_glyph;
};

#endif // RESIZABLEPIXMAP_H
