#include "QGraphicsEdgeItem.h"

QGraphicsEdgeItem::QGraphicsEdgeItem(const QGraphicsNodeItem *a, const QGraphicsNodeItem *b)
:QGraphicsLineItem(a->pos().x(), a->pos().y(), b->pos().x(), b->pos().y()),
 nodeA(a),
 nodeB(b),
 path(false),
 abstract(false)
{
    setZValue(1);
    setPen(QPen(Qt::gray, 1));
}

void QGraphicsEdgeItem::setPath(const bool& path) {
    this->path = path;

    if(path) {
        setPen(QPen(Qt::blue, 2));
        setZValue(3);
    }
    else {

        setPen(QPen(Qt::gray, 1));
    }

    this->update();
}

void QGraphicsEdgeItem::setAbstract(const bool& abstract) {
    this->abstract = abstract;

    if(abstract) {
        setPen(QPen(QColor(220,80,0), 1));
    }
    else {

        setPen(QPen(Qt::gray, 1));
    }

    this->update();
}


/*
QRectF QGraphicsEdgeItem::boundingRect() const
{
    QPoint posA = QPoint(0, 0);
    QPoint posB = QPoint((nodeB->x - nodeA->x) * 10, (nodeB->y - nodeA->y) * 10);

    return QRectF(std::min(posA.x(), posB.x()), std::min(posA.y(), posB.y()),
                  std::max(posA.x(), posB.x()), std::max(posA.y(), posB.y())
                 );
}

bool QGraphicsEdgeItem::contains ( const QPointF & point ) const
{
    return false;
}*/
/*
void QGraphicsEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   QGraphicsLineItem::paint(painter, option, widget);
}
*/
