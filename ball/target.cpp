#include "target.h"
#include "coreservice.h"

Target::Target(int size)
{
    geometry.setTopLeft(QPoint(CoreService::getInstance()->getWindowWidth() / 2,
                               CoreService::getInstance()->getWindowHeight() / 2));
    geometry.setSize(QSize(size, size));
    do {
    dx = random() % 3 - 1;
    dy = random() % 3 - 1;
    } while (dx ==0 || dy == 0);
}
QRect Target::getGeometry() const
{
    return geometry;
}

void Target::setGeometry(const QRect &value)
{
    geometry = value;
}

void Target::moveNext()
{
    CoreService *core = CoreService::getInstance();
    int height = core->getWindowHeight();
    int width = core->getWindowWidth();
    int limitX = core->getLimitX();
    int limitY = core->getLimitY();
    geometry.translate(dx, dy);
    if (geometry.x() < limitX) {
        dx = -dx;
        geometry.moveLeft(limitX);
    }
    if (geometry.y() < limitY) {
        dy = -dy;
        geometry.moveTop(limitY);
    }
    if (geometry.x() + geometry.width() > width) {
        dx = -dx;
        geometry.moveLeft(width- geometry.width());
    }
    if (geometry.y() + geometry.height() > height) {
        dy = -dy;
        geometry.moveTop(height - geometry.height() );
    }
}

