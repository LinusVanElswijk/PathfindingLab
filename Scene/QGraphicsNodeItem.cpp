#include "QGraphicsNodeItem.h"

QGraphicsNodeItem::QGraphicsNodeItem(const graphs::GridVertex& vertex, InteractionHandler& handler)
:vertex(vertex),
 handler(handler),
 start(false),
 goal(false),
 visited(false),
 evaluation(),
 expanded(false),
 path(false),
 abstract(false)
{
    setAcceptedMouseButtons ( handler.acceptedButtonsForNode() );
    this->setPos(vertex.getX() * 10, vertex.getY() * 10);
    setZValue(2);
}

QRectF QGraphicsNodeItem::boundingRect() const
{
    qreal width = 5 + 1;
    return QRectF(-width / 2, -width / 2, width, width);
}

bool QGraphicsNodeItem::contains ( const QPointF & point ) const
{
    qreal dx = point.x() - vertex.getX(),
          dy = point.y() - vertex.getY();

    return (dx * dx) + (dy * dy) < 2.5;
}

void QGraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(vertex.getOutgoingEdges().size() > 0) {
        painter->setBrush(QBrush(DEFAULT_NODE_COLOR));
    }
    else {
        painter->setBrush(QBrush(UNCONNECTED_NODE_COLOR));
    }

    if(abstract) {
        painter->setBrush(QBrush(ABSTRACT_NODE_COLOR));
    }

    if(visited) {
        painter->setBrush(QBrush(evaluationColor()));
    }


    if(path) {
        painter->setBrush(PATH_NODE_COLOR);
        this->setZValue(4);
    }

    if(isGoal()) {
        painter->setBrush(QBrush(START_NODE_COLOR));
    }
    if(isStart()) {
        painter->setBrush(QBrush(GOAL_NODE_COLOR));
    }

    if(!expanded) {
        painter->setPen(Qt::NoPen);
    }
    else {
        painter->setPen(Qt::black);
    }

    painter->drawEllipse(QPoint(0,0),3,3);
}

void QGraphicsNodeItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    handler.onNodeClick(vertex.getX(), vertex.getY(), this, event->button());
    update();
}

const QColor QGraphicsNodeItem::UNCONNECTED_NODE_COLOR = QColor(60,60,60);
const QColor QGraphicsNodeItem::DEFAULT_NODE_COLOR = QColor(140,140,140);
const QColor QGraphicsNodeItem::VISITED_NODE_COLOR = QColor(0, 100, 100);
const QColor QGraphicsNodeItem::PATH_NODE_COLOR = QColor(0,100,255);
const QColor QGraphicsNodeItem::START_NODE_COLOR = Qt::green;
const QColor QGraphicsNodeItem::GOAL_NODE_COLOR = Qt::red;
const QColor QGraphicsNodeItem::ABSTRACT_NODE_COLOR = QColor(220,80,0);
