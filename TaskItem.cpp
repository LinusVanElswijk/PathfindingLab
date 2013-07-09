#include "TaskItem.h"

TaskItem::TaskItem(const std::pair<Position, Position>& positions, QListWidget * parent, int type)
:QListWidgetItem(parent, type),
 start(positions.first),
 goal(positions.second)
{
}
