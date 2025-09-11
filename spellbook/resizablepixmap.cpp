#include "resizablepixmap.h"
#include <QPen>
#include <QGraphicsScene>
#include <QPainter>

ResizablePixmap::ResizablePixmap(int id, QPixmap pixmap, QString glyph) : m_id {id}, mPixmap{pixmap}, m_glyph{glyph}
{
    setOwner(this);
    setRect(0, 0, pixmap.width(), pixmap.height());
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
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

void ResizablePixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->drawPixmap(boundingRect(), mPixmap, mPixmap.rect());
    drawHandlesIfNecessary();
    painter->restore();
}

int ResizablePixmap::id()
{
    return m_id;
}

void ResizablePixmap::id(int id)
{
    m_id = id;
}

QPixmap ResizablePixmap::pixmap() const
{
    return mPixmap;
}

void ResizablePixmap::pixmap(const QPixmap &value)
{
    mPixmap = value;
}

QString ResizablePixmap::glyph() const
{
    return m_glyph;
}

int ResizablePixmap::type() const
{
    return Type;
}
