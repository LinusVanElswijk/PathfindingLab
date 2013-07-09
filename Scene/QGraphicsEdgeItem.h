#ifndef Q_GRAPHICS_EDGE_ITEM_H
#define Q_GRAPHICS_EDGE_ITEM_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

#include <iostream>

#include "QGraphicsNodeItem.h"

class QGraphicsEdgeItem : public QGraphicsLineItem
{
public:
    QGraphicsEdgeItem(const QGraphicsNodeItem *a, const QGraphicsNodeItem *b);

    void setPath(const bool& path);

    void setAbstract(const bool& abstract);

    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
/*
    QRectF boundingRect() const;

    bool contains ( const QPointF & point ) const;
    */

private:
    int x,y;

    bool path, abstract;

    const QGraphicsNodeItem *nodeA, *nodeB;
};

#endif // Q_GRAPHICS_NODE_ITEM_H
