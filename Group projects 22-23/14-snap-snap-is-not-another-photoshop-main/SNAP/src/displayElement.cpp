#include "../inc/displayElement.hpp"
#include "QStaticText"

QRectF displayElement::boundingRect() const
{
    return QRectF(0, 0, _width, _height);
}

void displayElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(rect_color);
    painter->drawEllipse(0, 0, _width, _height);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(0, 0 , _width, _height);
    painter->setBrush(Qt::black);
    QRectF rect(0 + 5, 0 +10 , _width, _height + 20);

    painter->drawText(rect, _displayText);
}

displayElement::displayElement(const QString &displayText, unsigned int element_id)
    : _displayText(displayText)
    , _element_id(element_id)
{
    this->setX(0);
    this->setY(0);
}

displayElement::displayElement()
{

}

displayElement::~displayElement()
{

}

displayElement::displayElement(const displayElement &d)
{
    _displayText = d._displayText;
    _element_id = d._element_id;
    _height = d._height;
    _width = d._width;
}

void displayElement::changeColor(QColor new_color)
{
    rect_color = new_color;
    update(this->x(), this->y(), _width, _height);
}

void displayElement::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> displayElement::getEdgeList() const
{
    return edgeList;
}

qreal displayElement::width() const
{
    return _width;
}

qreal displayElement::height() const
{
    return _height;
}
