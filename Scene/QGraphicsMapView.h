#ifndef QGRAPHICSMAPVIEW_H
#define QGRAPHICSMAPVIEW_H

#include <QGraphicsView>

#include <TileMap.h>

class QGraphicsMapView : public QGraphicsView
{
    Q_OBJECT

    public:
        explicit QGraphicsMapView(const TileMap& tilemap, QWidget *parent = 0);

    signals:

    public slots:

    private:
        void buildScenes();

        QGraphicsScene *scene;

        const TileMap& tileMap;
};

#endif // QGRAPHICSMAPVIEW_H
