#ifndef GAME3LAYOUT_H
#define GAME3LAYOUT_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>

namespace Ui {
class Game3Layout;
}

class Game3Layout : public QWidget
{
    Q_OBJECT

public:
    explicit Game3Layout(QWidget *parent = 0);
    ~Game3Layout();
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
    QPixmap image, greenBall, orangeBall;
    QTimer timer;
    QPoint startPoint, endPoint, mirrorStartPoint, mirrorEndPoint;
    bool mouseClicked;
    bool started;
    int level;
    Ui::Game3Layout *ui;
};

#endif // GAME3LAYOUT_H
