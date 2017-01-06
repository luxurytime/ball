#ifndef TARGET_H
#define TARGET_H

#include <QRect>

class Target
{
public:
    Target(int size);

    QRect getGeometry() const;
    void setGeometry(const QRect &value);

    void moveNext();

private:
    QRect geometry;
    int dx, dy;
};

#endif // TARGET_H
