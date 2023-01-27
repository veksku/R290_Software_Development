#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include "displayElement.hpp"

class displayElement;

class Edge : public QGraphicsItem
{
public:
    Edge(displayElement *source_element, displayElement *dest_element);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void adjust();

    displayElement *getSource() const;
    displayElement *getDest() const;

private:
    displayElement *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;

};

#endif // EDGE_H
