#ifndef BALL_H
#define BALL_H

#include <QPointF>
#include <QLine>
#include <math.h>
#include <QRect>
#include <QDebug>
#include <wall.h>

class Ball
{
public:
    Ball(double size);
    ~Ball();

    bool action();

    inline void moveNext() {
        posx += dx;
        posy += dy;
    }
    bool bounce();

    inline QPointF getPos() {
        return QPointF(posx, posy);
    }
    inline double getSize() {
        return size;
    }

    bool testCrash(QPointF startPoint, QPointF endPoint);
    bool bounceToLine(QPointF startPoint, QPointF endPoint);
    void bounceToLines();
    bool hitTarget();

    int getId() const;
    void setId(int value);

    double getDx() const;
    void setDx(double value);

    double getDy() const;
    void setDy(double value);

    double getPosx() const;
    void setPosx(double value);

    double getPosy() const;
    void setPosy(double value);

private:
    double posx, posy;
    double dx, dy;
    double size;
    int id;
    static int idCount;
};

#endif // BALL_H
