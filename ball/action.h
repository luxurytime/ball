#ifndef ACTION_H
#define ACTION_H

#include "ball.h"

class Action
{
public:
    Action();
    virtual bool onCrashWall(Ball *b);
    virtual bool onBounceToLine(const QPointF &startPoint, const QPointF &endPoint, Ball *b);
    virtual bool onHitTarget(Ball *b);
    virtual ~Action();
};

#endif // ACTION_H
