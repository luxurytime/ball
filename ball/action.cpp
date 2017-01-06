#include "action.h"
#include "coreservice.h"

Action::Action()
{
}

bool Action::onCrashWall(Ball *b)
{
    CoreService::getInstance()->scoreSub(1);
    return true;
}

bool Action::onBounceToLine(const QPointF &startPoint, const QPointF &endPoint, Ball *b)
{
    //CoreService::getInstance()->scoreSub(1);

    const double posx = b->getPos().x();
    const double posy = b->getPos().y();
    const double size = b->getSize();
    const double dx = b->getDx();
    const double dy = b->getDy();
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
        b->setDx(velocity.x());
        b->setDy(velocity.y());
        return true;
    } else {
        return false;
    }
}

bool Action::onHitTarget(Ball *b)
{
     CoreService::getInstance()->scoreAdd(2);
     CoreService::getInstance()->addVirtualBallInTarget();
     return true;
}

Action::~Action()
{

}
