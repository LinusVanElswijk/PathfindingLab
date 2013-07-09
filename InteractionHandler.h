#ifndef INTERACTIONHANDLER_H
#define INTERACTIONHANDLER_H

#include <QMouseEvent>

class QGraphicsNodeItem;

class InteractionHandler
{
    public:
        virtual Qt::MouseButtons acceptedButtonsForTile() = 0;
        virtual void onTileClick(const int& x, const int& y, const Qt::MouseButton& button) = 0;

        virtual Qt::MouseButtons acceptedButtonsForNode() = 0;
        virtual void onNodeClick(const int& x, const int& y, QGraphicsNodeItem* const node, const Qt::MouseButton& button) = 0;
};

#endif // INTERACTIONHANDLER_H
