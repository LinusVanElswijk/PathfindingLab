#ifndef TASKITEM_H
#define TASKITEM_H

#include <QListWidgetItem>
#include <utility>

#include "position.h"

class TaskItem: public QListWidgetItem
{
public:
    explicit TaskItem(const std::pair<Position, Position>& positions, QListWidget * parent = 0, int type = Type);

    enum State {
        INVALID, VALID, CALCULATING, CALCULATED
    };

private:
    const Position start, goal;


};

#endif // TASKITEM_H
