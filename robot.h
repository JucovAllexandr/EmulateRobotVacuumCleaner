#ifndef ROBOT_H
#define ROBOT_H

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QVector2D>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
class Robot
{

    float sx, sy;
    float diameter;
    float angle;
    float x,y;
    QGraphicsEllipseItem *circle;
    QGraphicsLineItem *directionLine;
    QStyleOptionGraphicsItem style;
public:

    Robot(float x, float y, float diameter);
    void draw(QPainter *painter);
    void move(int step, int angle);
    void scale(float factor);
    void checkCollision(QVector<QGraphicsItem *> &items);

};

#endif // ROBOT_H
