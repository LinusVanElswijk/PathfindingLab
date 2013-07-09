#include "QGraphicsMapView.h"

QGraphicsMapView::QGraphicsMapView(const TileMap& tileMap, QWidget *parent)
:QGraphicsView(parent),
 tileMap(tileMap)
{

}
