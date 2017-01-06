#include "wall.h"
#include "coreservice.h"
#include <QObject>

int Wall::idCount = 0;

Wall::Wall(const QPoint &startPoint, const QPoint &endPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    id = idCount++;
    age = 0;
    //timer.setInterval(10000);
    //QObject::connect(&timer, SIGNAL(timeout()), this, deleteSelf);
}

/*Wall::Wall(const Wall &other)
{
    this->startPoint = other.startPoint;
    this->endPoint = other.endPoint;
    id = other.id;
    timer = other.timer;
}
*/
QPoint Wall::getStartPoint() const
{
    return startPoint;
}

void Wall::setStartPoint(const QPoint &value)
{
    startPoint = value;
}
QPoint Wall::getEndPoint() const
{
    return endPoint;
}

void Wall::setEndPoint(const QPoint &value)
{
    endPoint = value;
}

bool Wall::deleteSelf()
{
    return CoreService::getInstance()->removeWall(id);
}
int Wall::getAge() const
{
    return age;
}

void Wall::setAge(int value)
{
    age = value;
}

int Wall::getId() const
{
    return id;
}

void Wall::setId(int value)
{
    id = value;
}



