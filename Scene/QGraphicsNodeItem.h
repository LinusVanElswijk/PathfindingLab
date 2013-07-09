#ifndef Q_GRAPHICS_NODE_ITEM_H
#define Q_GRAPHICS_NODE_ITEM_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include <iostream>

#include "Task.h"
#include "GridVertex.hpp"
#include "InteractionHandler.h"

class QGraphicsTileMapScene;

class QGraphicsNodeItem : public QGraphicsItem
{
public:
    QGraphicsNodeItem(const graphs::GridVertex& vertex, InteractionHandler& handler);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;

    bool contains ( const QPointF & point ) const;
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );

    const graphs::GridVertex& getVertex() const {
        return vertex;
    }

    bool isStart() {
        return start;
    }

    bool isGoal() {
        return goal;
    }

    void setStart(const bool& start) {
        this->start = start;
    }

    void setGoal(const bool& goal) {
        this->goal = goal;
    }

    void setVisited(const bool& visited) {
        this->visited = visited;
    }

    void setExpanded(const bool& expanded) {
        this->expanded = expanded;
    }

    void setAbstract(const bool& abstract) {
        this->abstract = abstract;
    }

    graphs::Real clamp(graphs::Real value) {
        return value < 0.0 ? 0.0 : (value > 1.0 ? 1.0 : value);
    }

    void setEvaluation(const graphs::Real& evaluation) {
        this->evaluation = this->clamp(evaluation);
    }

    void setPath(const bool& path) {
        this->path = path;
    }

private:
    const graphs::GridVertex& vertex;
    InteractionHandler& handler;

    bool start, goal, visited, expanded, path, abstract;

    QColor evaluationColor() const {
        return QColor::fromRgbF(evaluation, 1.0 - evaluation, 0);
    }

    graphs::Real evaluation;

public:
    static const QColor UNCONNECTED_NODE_COLOR,
                        DEFAULT_NODE_COLOR,
                        VISITED_NODE_COLOR,
                        PATH_NODE_COLOR,
                        START_NODE_COLOR,
                        GOAL_NODE_COLOR,
                        ABSTRACT_NODE_COLOR;
};

#endif // Q_GRAPHICS_NODE_ITEM_H
