#include "coreservice.h"

CoreService* CoreService::instance = NULL;

CoreService::~CoreService()
{
    delete ballList;
    delete wallList;
    delete virtualBallList;
    if (target)
        delete target;
    if (action)
        delete action;
}

CoreService *CoreService::getInstance()
{
    if (instance == NULL)
        instance = new CoreService();
    return instance;
}

void CoreService::addBall(Ball b)
{
    ballList->push_back(b);
}

void CoreService::addWall(Wall w)
{
    wallList->push_back(w);
}

CoreService::CoreService()
{
    ballList = new list<Ball>();
    wallList = new list<Wall>();
    virtualBallList = new list<Ball>();
    action = new Action();
    target = NULL;
    score = 10;
    frameCount = 0;
    limitX = 0;
    limitY = 0;
}
int CoreService::getLimitY() const
{
    return limitY;
}

void CoreService::setLimitY(int value)
{
    limitY = value;
}

int CoreService::getLimitX() const
{
    return limitX;
}

void CoreService::setLimitX(int value)
{
    limitX = value;
}

list<Ball> *CoreService::getVirtualBallList() const
{
    return virtualBallList;
}

void CoreService::setVirtualBallList(list<Ball> *value)
{
    virtualBallList = value;
}

void CoreService::addVirtualBallInTarget()
{
    for (int count = 0; count < 15; count++) {
        Ball b(16);
        b.setPosx(target->getGeometry().center().x());
        b.setPosy(target->getGeometry().center().y());
        virtualBallList->push_back(b);
    }
}

int CoreService::getScore() const
{
    return score;
}

void CoreService::setScore(int value)
{
    score = value;
}

void CoreService::scoreAdd(int increase)
{
    score += increase;
}

void CoreService::scoreSub(int decrease)
{
    score -= decrease;
}

Target *CoreService::getTarget() const
{
    return target;
}

void CoreService::setTarget(Target *value)
{
    target = value;
}

void CoreService::removeTarget()
{
    delete target;
    target = NULL;
}

Action *CoreService::getAction() const
{
    return action;
}

void CoreService::setActionAndDeleteOld(Action *value)
{
    if (action != NULL)
        delete action;
    action = value;
}


QRect CoreService::getTargetGeometry() const
{
    return target?target->getGeometry():QRect(-10, -10, 0, 0);
}

void CoreService::setTargetGeometry(const QRect &value)
{
    target->setGeometry(value);
}

int CoreService::getWindowWidth() const
{
    return windowWidth;
}

void CoreService::setWindowWidth(int value)
{
    windowWidth = value;
}

int CoreService::getWindowHeight() const
{
    return windowHeight;
}

void CoreService::setWindowHeight(int value)
{
    windowHeight = value;
}

list<Wall> *CoreService::getWallList() const
{
    return wallList;
}

void CoreService::setWallList(list<Wall> *value)
{
    wallList = value;
}

bool CoreService::removeBall(int id)
{
    for (list<Ball>::iterator it = ballList->begin(); it != ballList->end(); it++) {
        if (it->getId() == id) {
            it = ballList->erase(it);
            return true;
        }
    }
    return false;
}

bool CoreService::removeWall(int id)
{
    for (list<Wall>::iterator it = wallList->begin(); it != wallList->end(); it++) {
        if (it->getId() == id) {
            it = wallList->erase(it);
            return true;
        }
    }
    return false;
}

void CoreService::resetAllElementExpectScore()
{
    int tempScore = score;
    delete instance;
    instance = new CoreService();
    setScore(tempScore);
}

bool CoreService::ballsAction()
{
    frameCount++;
    if (virtualBallList) {
        int size = virtualBallList->size();
        if (frameCount % 20 == 0 && size) {
            size /= 10;
            do {
                virtualBallList->pop_front();
            } while(size--);
        }
    }
    for (list<Ball>::iterator it = virtualBallList->begin(); it != virtualBallList->end(); it++) {
        it->moveNext();
        it->bounce();
    }
    bool anyHit = false;
    for (list<Ball>::iterator it = ballList->begin(); it != ballList->end(); it++) {
        if (it->action()) {
            it = ballList->erase(it);
            if (it == ballList->begin() || it == ballList->end())
                CoreService::getInstance()->scoreAdd(10);
            anyHit = true;
        }
    }
    return anyHit;
}

void CoreService::checkWallsAge()
{
    for (list<Wall>::iterator it = wallList->begin(); it != wallList->end(); it++) {
        it->setAge(it->getAge() + 10);
        if (it->getAge() > MAX_AGE) {
            it = wallList->erase(it);
        }
    }
}

void CoreService::targetAction()
{

}

list<Ball> *CoreService::getBallList() const
{
    return ballList;
}

void CoreService::setBallList(list<Ball> *value)
{
    ballList = value;
}

