#include "../inc/edge.hpp"
#include <QPainter>
#include <QtMath>

Edge::Edge(displayElement *source_element, displayElement *dest_element)
    : source(source_element)
    , dest(dest_element)
{
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
            return QRectF();

        qreal penWidth = 1;

        return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                          destPoint.y() - sourcePoint.y()))
            .normalized();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!source || !dest)
            return;

    //QLineF line(mapFromItem(source, source->width()/2.0, source->height()/2.0), mapFromItem(dest, dest->width(), dest->height()));
    QLineF line(QPointF(source->x() + source->width()/2.0, source->y() + source->height()/2.0), QPointF(dest->x() + dest->width()/2.0, dest->y() + dest->height()/2.0));

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

}

void Edge::adjust()
{
    if (!source || !dest)
            return;

        QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
        qreal length = line.length();

        prepareGeometryChange();
        sourcePoint = QPoint(source->x() + source->width()/2.0, source->y() + source->height() / 2.0);
        destPoint = QPoint(dest->x() + source->x() + source->width()/2.0, dest->y() + source->height() / 2.0);

        /*if (length > qreal(20.)) {
            QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
            sourcePoint = line.p1()+ QPoint(50,-10);
            destPoint = line.p2() ;//- edgeOffset;
        } else {
            sourcePoint = destPoint = line.p1();
        }*/
}

displayElement *Edge::getSource() const
{
    return source;
}

displayElement *Edge::getDest() const
{
    return dest;
}
