#include "mainlayout.h"
#include "ui_mainlayout.h"
#include <QMessageBox>
#include "coreservice.h"
#include <QPen>
#include "target.h"
#include "mainwindow.h"

MainLayout::MainLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainLayout)
{
    ui->setupUi(this);
    started = false;
    level = 1;
    image.load(":/image/image.png");
    orangeBall.load(":/image/orange.png");

    timer.setInterval(10);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkWalls()));
    timer.start();
}

MainLayout::~MainLayout()
{
    delete ui;
}

void MainLayout::start()
{
    CoreService::getInstance()->resetAllElementExpectScore();
    for (int count = 0; count < level * level; count++) {
        CoreService::getInstance()->addBall(48);
    }
    for (int count = 0; count < level ; count++) {
        CoreService::getInstance()->setTarget(new Target(64));
    }
}

void MainLayout::paintEvent(QPaintEvent *event)
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
    pen.setWidth(5);
    pen.setColor(Qt::lightGray);

    QPainter p(this);
    p.setPen(pen);
    if (mouseClicked)
        p.drawLine(startPoint, endPoint);

    // paint target
    if (target)
        p.drawPixmap(target->getGeometry().topLeft(), orangeBall.scaled(target->getGeometry().size()));

    // paint balls
    for (list<Ball>::iterator it = ballList->begin(); it != ballList->end(); it++) {
        p.drawPixmap(it->getPos().x(), it->getPos().y(), it->getSize(), it->getSize(), image.scaled(QSize(it->getSize(), it->getSize())));
    }

    // paint walls
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

void MainLayout::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        endPoint = startPoint;
        mouseClicked = true;
    }
    event->accept();
}

void MainLayout::mouseReleaseEvent(QMouseEvent *event)
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

void MainLayout::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        endPoint = event->pos();
    }
    event->accept();
}

void MainLayout::resizeEvent(QResizeEvent *event)
{
    CoreService::getInstance()->setWindowHeight(this->height());
    CoreService::getInstance()->setWindowWidth(this->width());
    event->accept();
}

void MainLayout::checkWalls()
{
    CoreService::getInstance()->checkWallsAge();
}

void MainLayout::on_startBtn_clicked(bool checked)
{
    if (checked) {
        started = true;
        ui->startBtn->setText("pause");
    } else {
        started = false;
        ui->startBtn->setText("start");
    }
}
