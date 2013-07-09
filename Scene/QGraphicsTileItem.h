#ifndef Q_GRAPHICS_TILE_ITEM_H
#define Q_GRAPHICS_TILE_ITEM_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneEvent>

#include <iostream>
#include "TileMap.h"
#include "InteractionHandler.h"

class QGraphicsTileItem : public QGraphicsItem
{
public:
    QGraphicsTileItem(const int& x, const int& y, const TileMap& tileMap, InteractionHandler& interaction);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setLineOfSightCheck(const bool& check);

    QRectF boundingRect() const;
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );

private:
    const TileMap& tileMap;
    int x,y;
    InteractionHandler& handler;
    bool lineOfSightCheck;
};

#endif // Q_GRAPHICS_TILE_ITEM_H
