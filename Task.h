#ifndef TASK_H
#define TASK_H

#include <QPoint>

class SearchTask
{
public:
    SearchTask()
    :start(NULL), goal(NULL)
    { }

    SearchTask(const QPoint& start, const QPoint& goal)
    :start(NULL), goal(NULL)
    {
        setStart(start);
        setGoal(goal);
    }

    bool isSpecified() {
        return start && goal;
    }

    void setStart(const QPoint& start) {
        setStart(&start);
    }

    void setGoal(const QPoint& goal) {
        setGoal(&goal);
    }

    void setStart(const QPoint* const start) {
        set(this->start, start);
    }

    void setGoal(const QPoint* const goal) {
        set(this->goal, goal);
    }

    const QPoint* getStart() const {
        return start;
    }

    const QPoint* getGoal() const {
        return goal;
    }

private:

    void set(const QPoint*& oldValue, const QPoint* const newValue) {
        if(oldValue) {
            delete oldValue;
            oldValue = NULL;
        }

        if(newValue)
            oldValue = new QPoint(*newValue);
    }

    const QPoint* start;
    const QPoint* goal;
};

#endif // TASK_H
