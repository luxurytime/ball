#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>
#include <QTime>
#include <QDebug>
#include "ball.h"

namespace Ui {
class MainLayout;
}

class MainLayout : public QWidget
{
    Q_OBJECT

public:
    explicit MainLayout(QWidget *parent = 0);
    ~MainLayout();
    void start();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void checkWalls();

    void on_startBtn_clicked(bool checked);

private:
    Ui::MainLayout *ui;
    QPixmap image, orangeBall;
    QTimer timer;
    QPoint startPoint, endPoint;
    bool mouseClicked;
    bool started;
    int level;
};

#endif // MAINLAYOUT_H
