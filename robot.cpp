#include "robot.h"
#include <QtMath>
#include <QDebug>
Robot::Robot(int x, int y):
    x(x),y(y),diameter(50),sx(x),sy(y)
{
    angle = 180;
}

void Robot::draw(QPainter *painter)
{
    painter->setPen(QPen(QBrush(Qt::black),3));
    painter->drawEllipse(x,y,diameter,diameter);
    float cx = x+diameter/2.f;
    float cy = y+diameter/2.f;
    float radius = diameter/2.f;
    float xr = x-0;
    float yr = y-0;
    float d = qRound( sqrt((xr*xr) + (yr*yr)));
    painter->drawLine(cx,cy,qRound(cos(qDegreesToRadians(angle))*radius)+cx,abs(qRound(-sin(qDegreesToRadians(angle))*radius)+cy));
    //painter->rotate(angle);

}

void Robot::move(int step,int angle)
{
    this->angle = angle;
    this->x += cos(qDegreesToRadians(this->angle))*step;
    this->y += -sin(qDegreesToRadians(this->angle))*step;
}



