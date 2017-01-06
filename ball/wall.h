#ifndef WALL_H
#define WALL_H

#include <QPoint>
#include <QObject>

class Wall
{
public:
    Wall(const QPoint &startPoint, const QPoint &endPoint);
    //Wall(const Wall &other);

    QPoint getStartPoint() const;
    void setStartPoint(const QPoint &value);

    QPoint getEndPoint() const;
    void setEndPoint(const QPoint &value);
    int getId() const;
    void setId(int value);
    bool deleteSelf();

    int getAge() const;
    void setAge(int value);

private:
    QPoint startPoint;
    QPoint endPoint;
    int age;
    int id;
    static int idCount;
};

#endif // WALL_H
