#include "ball.h"
#include "coreservice.h"

int Ball::idCount = 0;

Ball::Ball(double size)
{
    posx = random() % 600;
    posy = random() % 600;
    do {
        dx = random() % 5 - 2;
        dy = random() % 5 - 2;
    } while(dx == 0 && dy == 0);
    id = idCount++;
    this->size = size;
}

Ball::~Ball()
{

}

bool Ball::action() {
    moveNext();
    if (bounce())
        CoreService::getInstance()->getAction()->onCrashWall(this);
    bounceToLines();
    return hitTarget();
}

bool Ball::bounce() {
    CoreService *core = CoreService::getInstance();
    int height = core->getWindowHeight();
    int width = core->getWindowWidth();
    int limitX = core->getLimitX();
    int limitY = core->getLimitY();
    if (posx < limitX) {
        dx = -dx;
        posx = limitX;
        return true;
    }
    if (posx + size > width) {
        dx = -dx;
        posx = width - size;
        return true;
    }
    if (posy < limitY) {
        dy = -dy;
        posy = limitY;
        return true;
    }
    if (posy + size > height) {
        dy = -dy;
        posy = height - size;
        return true;
    }
    return false;
}

bool Ball::testCrash(QPointF startPoint, QPointF endPoint) {
    QPointF center = QRect(posx, posy, size, size).center();
    double radius_s = size * size / 4;
    QPointF temp = center - startPoint;
    double centerToStartPoint_s = temp.x() * temp.x() + temp.y() * temp.y();
    temp = center - endPoint;
    double centerToEndPoint_s = temp.x() * temp.x() + temp.y() * temp.y();
    temp = endPoint - startPoint;
    double endPointToStartPoint_s = temp.x() * temp.x() + temp.y() * temp.y();
    double endPointToVerticalPoint_s = centerToEndPoint_s - radius_s;
    double startPointToVerticalPoint_s = centerToStartPoint_s - radius_s;
    if (sqrt(startPointToVerticalPoint_s) + sqrt(endPointToVerticalPoint_s) - sqrt(endPointToStartPoint_s) < 0) {
        return true;
    }
    return false;
}

bool Ball::bounceToLine(QPointF startPoint, QPointF endPoint) {
    QPointF center = QRect(posx, posy, size, size).center();
    double radius_s = size * size / 4;
    QPointF temp = center - startPoint;
    double centerToStartPoint_s = temp.x() * temp.x() + temp.y() * temp.y();
    temp = center - endPoint;
    double centerToEndPoint_s = temp.x() * temp.x() + temp.y() * temp.y();
    temp = endPoint - startPoint;
    double endPointToStartPoint_s = temp.x() * temp.x() + temp.y() * temp.y();
    double endPointToVerticalPoint_s = centerToEndPoint_s - radius_s;
    double startPointToVerticalPoint_s = centerToStartPoint_s - radius_s;
    if (sqrt(startPointToVerticalPoint_s) + sqrt(endPointToVerticalPoint_s) - sqrt(endPointToStartPoint_s) < 0) {
        temp = endPoint - startPoint;
        QPointF velocity(dx, dy);
        double dotProduct  = QPointF::dotProduct(temp, velocity);
        double velocity_s = dx * dx + dy * dy;
        double cos = dotProduct / (sqrt(dx * dx + dy * dy) * sqrt(temp.x() * temp.x() + temp.y() * temp.y()));
        double verticalVectorLength = sqrt(velocity_s) * sqrt(1.0 - cos * cos) * 2;
        QPointF unitVerticalVertor = QPointF(temp.y() / sqrt(temp.x() * temp.x() + temp.y() * temp.y()), -temp.x() / sqrt(temp.x() * temp.x() + temp.y() * temp.y()));
        /*qDebug() << "cos " << cos;
        qDebug() << "verticalVertorLength" << verticalVectorLength;
        qDebug() << "dx: " << dx << ",dy: " << dy;

        qDebug() << "unit vertical vertor: " << unitVerticalVertor;
        qDebug() << "vertical rate:" << QPointF::dotProduct(temp, unitVerticalVertor);
        */
        QPointF verticalVector = verticalVectorLength * unitVerticalVertor;
        if (QPointF::dotProduct(verticalVector, velocity) > 0)
            verticalVector = -verticalVector;
        velocity += verticalVector;
        dx = velocity.x();
        dy = velocity.y();
        return true;
    } else {
        return false;
    }
}

void Ball::bounceToLines()
{
    CoreService * core = CoreService::getInstance();
    list<Wall> *wallList = core->getWallList();
    for (list<Wall>::iterator it = wallList->begin(); it != wallList->end(); it++) {
        if (testCrash((*it).getStartPoint(), (*it).getEndPoint())) {
            //bounceToLine((*it).getStartPoint(), (*it).getEndPoint());
            CoreService::getInstance()->getAction()->onBounceToLine((*it).getStartPoint(), (*it).getEndPoint(), this);
            return;
        }
    }
}

bool Ball::hitTarget()
{
    QRect target = CoreService::getInstance()->getTargetGeometry();
    if (QRect(posx, posy, size, size).intersects(target)) {
        CoreService::getInstance()->getAction()->onHitTarget(this);
        return true;
    }
    return false;
}
int Ball::getId() const
{
    return id;
}

void Ball::setId(int value)
{
    id = value;
}
double Ball::getDx() const
{
    return dx;
}

void Ball::setDx(double value)
{
    dx = value;
}
double Ball::getDy() const
{
    return dy;
}

void Ball::setDy(double value)
{
    dy = value;
}
double Ball::getPosy() const
{
    return posy;
}

void Ball::setPosy(double value)
{
    posy = value;
}

double Ball::getPosx() const
{
    return posx;
}

void Ball::setPosx(double value)
{
    posx = value;
}





