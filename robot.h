#ifndef ROBOT_H
#define ROBOT_H

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QVector2D>
class Robot
{
    float x,y;
    float sx, sy;
    int diameter;
    float angle;
public:
    Robot(int x, int y);
    void draw(QPainter *painter);
    void move(int step, int angle);
};

#endif // ROBOT_H
