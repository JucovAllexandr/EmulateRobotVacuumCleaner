#ifndef WORLDPAINTER_H
#define WORLDPAINTER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QKeyEvent>
#include <QSpinBox>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include "robot.h"
enum DrawShape{None, Rectangle, Ellipse, Triangle};
class WorldPainter : public QWidget
{
    Q_OBJECT

    QTimer timer;
    QSize mapSize;
    Robot *robot;
    int x=0,y=0;
    int tranX = 0, tranY = 0;
    int startTranX = 0, startTranY = 0;
    bool isCanTranslate = 0, isCanDrawShape = 0;
    float scale = 1;
    DrawShape drawShape = DrawShape::None;
    QPoint shape1, shape2;
    QStyleOptionGraphicsItem styleOption;
    QVector<QGraphicsItem*> shapes;

public:
    explicit WorldPainter(QWidget *parent = nullptr);
    void setMapSize(QSize sz);
    void setDrawShape(DrawShape type);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


};

#endif // WORLDPAINTER_H
