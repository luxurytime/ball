#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>
#include <QTime>
#include <QDebug>
#include "ball.h"
#include "mainlayout.h"
#include "game2layout.h"
#include "game3layout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void gameInit();

private:
    Ui::MainWindow *ui;
    MainLayout *mainLayout;
    Game2Layout *game2Layout;
    Game3Layout *game3Layout;
    void reset();
    void gameStart();

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_bounceAndRollBtn_clicked();
    void on_linkBreakerBtn_clicked();
    void on_mIrrorMasterBtn_clicked();
};

#endif // MAINWINDOW_H
