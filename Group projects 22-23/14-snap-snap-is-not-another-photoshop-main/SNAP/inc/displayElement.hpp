#ifndef DISPLAYELEMENT_HPP
#define DISPLAYELEMENT_HPP

#include <QGraphicsItem>
#include <QPainter>
#include "edge.hpp"

class Edge;

class displayElement : public QGraphicsItem
{
    // QGraphicsItem interface
public:
    displayElement(const QString &displayText, unsigned int element_id);
    displayElement();
    ~displayElement();

    displayElement(const displayElement &d);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    void changeColor(QColor new_color);
    void addEdge(Edge *edge);

    QList<Edge *> getEdgeList() const;

    qreal width() const;
    qreal height() const;

private:
    QString _displayText = "";
    unsigned _element_id;
    qreal _width = 100;
    qreal _height = 80;
    QColor rect_color = QColor(204,205,245);

    QList<Edge *> edgeList;
    QPointF newPos;
};

#endif // DISPLAYELEMENT_HPP
