#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "coreservice.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->wallPaperLabel->setVisible(false);
    mainLayout = NULL;
    game2Layout = NULL;
    game3Layout = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    if (mainLayout) {
        delete mainLayout;
        mainLayout = NULL;
    }
    if (game2Layout) {
        delete game2Layout;
        game2Layout = NULL;
    }
    if (game3Layout) {
        delete game3Layout;
        game3Layout = NULL;
    }
}

void MainWindow::gameStart()
{
    ui->gameSelectLayout->setVisible(false);
    ui->wallPaperLabel->setVisible(true);
}

void MainWindow::gameInit()
{
    //this->resize(550, 500);
    //reset();
    //ui->gameSelectLayout->setVisible(true);
    //ui->wallPaperLabel->setVisible(false);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (mainLayout)
        mainLayout->resize(this->size());
    if (game2Layout)
        game2Layout->resize(this->size());
    if (game3Layout) {
        game3Layout->resize(this->size());
    }
    ui->wallPaperLabel->resize(this->size());
    ui->gameSelectLayout->resize(this->size());
    event->accept();
}

void MainWindow::on_bounceAndRollBtn_clicked()
{
    ui->wallPaperLabel->setStyleSheet(QStringLiteral("background-image: url(:/image/wall.jpg);"));
    reset();
    gameStart();
    mainLayout = new MainLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setGeometry(QRect(0, 0, 400, 300));
    mainLayout->setStyleSheet(QStringLiteral("background-image: url();"));
    mainLayout->setVisible(true);
    mainLayout->start();
    this->resize(400, 300);
}

void MainWindow::on_linkBreakerBtn_clicked()
{
    ui->wallPaperLabel->setStyleSheet(QStringLiteral("background-image: url(:/image/OutlandDirt01.png);"));
    reset();
    gameStart();

    game2Layout = new Game2Layout(this);
    game2Layout->setObjectName(QStringLiteral("game2Layout"));
    game2Layout->setGeometry(QRect(0, 0, 400, 300));
    game2Layout->setStyleSheet(QStringLiteral("background-image: url();"));
    game2Layout->setVisible(true);
    game2Layout->start();
    this->resize(400, 300);
}

void MainWindow::on_mIrrorMasterBtn_clicked()
{
    ui->wallPaperLabel->setStyleSheet(QStringLiteral("background-image: url(:/image/OutlandSand01.png);"));
    reset();
    gameStart();
    game3Layout = new Game3Layout(this);
    game3Layout->setObjectName(QStringLiteral("game3Layout"));
    game3Layout->setGeometry(0, 0, 0, 0);
    game3Layout->setStyleSheet(QStringLiteral("background-image: url();"));
    game3Layout->setVisible(true);
    game3Layout->start();
    this->resize(400, 300);
}
