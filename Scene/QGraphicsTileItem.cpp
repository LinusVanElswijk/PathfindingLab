#include "QGraphicsTileItem.h"

QGraphicsTileItem::QGraphicsTileItem(const int& x, const int& y, const TileMap& tileMap, InteractionHandler &handler)
:tileMap(tileMap),
 x(x),
 y(y),
 handler(handler),
 lineOfSightCheck(false)
{
    setAcceptedMouseButtons ( handler.acceptedButtonsForTile() );
    this->setPos(x * 10, y * 10);
    setZValue(0);
}

QRectF QGraphicsTileItem::boundingRect() const
{
    qreal penWidth = 0;
    return QRectF(-penWidth / 2, -penWidth / 2, 10 + penWidth, 10 + penWidth);
}

void QGraphicsTileItem::setLineOfSightCheck(const bool& check) {
    lineOfSightCheck = check;
    this->update();
}

void QGraphicsTileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    //if(lod >= 0.5)
    QRectF rect(0, 0, 10, 10);

    QBrush brush;

    if(tileMap(x,y))
        brush = QBrush(Qt::black);
    else
        brush = QBrush(Qt::white);

    if(lineOfSightCheck) {
        brush = QBrush(Qt::blue);
    }

    painter->setPen(Qt::NoPen);
    painter->fillRect(rect, brush);

    painter->drawRect(rect);
}

void QGraphicsTileItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    handler.onTileClick(x,y, event->button());
    this->update();
}
