#include "game2layout.h"
#include "ui_game2layout.h"
#include "coreservice.h"
#include <QPen>
#include <QPainter>

Game2Layout::Game2Layout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game2Layout)
{
    ui->setupUi(this);

    started = false;
    level = 1;
    image.load(":/image/image.png");
    greenBall.load(":/image/green.png");
    orangeBall.load(":/image/orange.png");

    timer.setInterval(10);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkWalls()));
    timer.start();
}

Game2Layout::~Game2Layout()
{
    delete ui;
}

void Game2Layout::start()
{
    CoreService::getInstance()->resetAllElementExpectScore();
    for (int count = 0; count < level * level; count++) {
        CoreService::getInstance()->addBall(48);
    }
    CoreService::getInstance()->setTarget(new Target(64));
}

void Game2Layout::paintEvent(QPaintEvent *event)
{
    Target *target =  CoreService::getInstance()->getTarget();
    if (started) {
        CoreService::getInstance()->ballsAction();
        if (target)
            target->moveNext();
        if (CoreService::getInstance()->getBallList()->size() == 0) {
            CoreService::getInstance()->removeTarget();
            level++;
            start();
        }
    }

    // update score display
    ui->scoreLcdNumber->display(CoreService::getInstance()->getScore());

    list<Ball> *ballList = CoreService::getInstance()->getBallList();
    QPen pen;

    QPainter p(this);

    // paint target
    if (target)
        p.drawPixmap(target->getGeometry().topLeft(), orangeBall.scaled(target->getGeometry().size()));

    // paint balls
    pen.setWidth(2);
    pen.setColor(Qt::green);
    p.setPen(pen);
    for (list<Ball>::iterator it = ballList->begin(); it != ballList->end(); it++) {
        QRectF temp(it->getPosx(), it->getPosy(), it->getSize(), it->getSize());
        list<Ball>::iterator tempIt = it;
        tempIt++;

        if (it == ballList->begin() || tempIt == ballList->end()) {
            p.drawPixmap(temp.toRect(), greenBall.scaled(QSize(it->getSize(), it->getSize())));
        } else {
            p.drawPixmap(temp.toRect(), image.scaled(QSize(it->getSize(), it->getSize())));
        }
        if (tempIt != ballList->end()) {

            QRectF next(tempIt->getPosx(), tempIt->getPosy(), tempIt->getSize(), tempIt->getSize());

            p.drawLine(temp.center(), next.center());
        }
    }

    // paint walls
    pen.setWidth(5);
    pen.setColor(Qt::lightGray);
    p.setPen(pen);
    if (mouseClicked)
        p.drawLine(startPoint, endPoint);
    list<Wall> *wallList = CoreService::getInstance()->getWallList();
    for (list<Wall>::iterator it = wallList->begin(); it != wallList->end(); it++) {
        p.drawLine(it->getStartPoint(), it->getEndPoint());
    }

    // paint and move virtual balls
    list<Ball> *virtualBallList = CoreService::getInstance()->getVirtualBallList();
    for (list<Ball>::iterator it = virtualBallList->begin(); it != virtualBallList->end(); it++) {
        p.drawPixmap(it->getPos().x(), it->getPos().y(), it->getSize(), it->getSize(), image.scaled(QSize(it->getSize(), it->getSize())));
    }

    event->accept();
}

void Game2Layout::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        endPoint = startPoint;
        mouseClicked = true;
    }
    event->accept();
}

void Game2Layout::mouseReleaseEvent(QMouseEvent *event)
{
    list<Ball> *ballList = CoreService::getInstance()->getBallList();
    for (list<Ball>::iterator it = ballList->begin(); it != ballList->end(); it++) {
        if (it->bounceToLine(startPoint, endPoint))
            return;
    }
    Wall temp(startPoint, endPoint);
    CoreService *core = CoreService::getInstance();
    core->getWallList()->push_back(temp);
    mouseClicked = false;
    event->accept();
}

void Game2Layout::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        endPoint = event->pos();
    }
    event->accept();
}

void Game2Layout::resizeEvent(QResizeEvent *event)
{
    CoreService::getInstance()->setWindowHeight(this->height());
    CoreService::getInstance()->setWindowWidth(this->width());
    event->accept();
}

void Game2Layout::checkWalls()
{
    CoreService::getInstance()->checkWallsAge();
}

void Game2Layout::on_startBtn_clicked(bool checked)
{
    if (checked) {
        started = true;
        ui->startBtn->setText("pause");
    } else {
        started = false;
        ui->startBtn->setText("start");
    }
}
