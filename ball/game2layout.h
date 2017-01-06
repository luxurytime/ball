#ifndef GAME2LAYOUT_H
#define GAME2LAYOUT_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>

namespace Ui {
class Game2Layout;
}

class Game2Layout : public QWidget
{
    Q_OBJECT

public:
    explicit Game2Layout(QWidget *parent = 0);
    ~Game2Layout();
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
    QPoint startPoint, endPoint;
    bool mouseClicked;
    bool started;
    int level;
    Ui::Game2Layout *ui;
};

#endif // GAME2LAYOUT_H
