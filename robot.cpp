#include "robot.h"
#include <QtMath>
#include <QDebug>
Robot::Robot(float x, float y, float diameter):
    x(x),y(y),diameter(diameter),sx(x),sy(y)
{
    angle = 180;
    circle = new QGraphicsEllipseItem(x, y, diameter, diameter);
    directionLine = new QGraphicsLineItem(x + (diameter / 2), y + (diameter / 2), x + diameter, y + (diameter / 2));

    directionLine->setPen(QPen(QBrush(Qt::black),3));
    circle->setPen(QPen(QBrush(Qt::black),3));

}

void Robot::draw(QPainter *painter)
{

   /* painter->setPen(QPen(QBrush(Qt::black),3));
    painter->drawEllipse(x,y,diameter,diameter);*/
    float cx = x+diameter/2.f;
    float cy = y+diameter/2.f;
    float radius = diameter/2.f;
    float xr = x-0;
    float yr = y-0;
    float d = qRound( sqrt((xr*xr) + (yr*yr)));

    circle->setRect(x,y,diameter,diameter);
    directionLine->setLine(cx,cy,qRound(cos(qDegreesToRadians(angle))*radius)+cx,abs(qRound(-sin(qDegreesToRadians(angle))*radius)+cy));
    circle->paint(painter, &style);
    directionLine->paint(painter, &style);

}

void Robot::move(int step,int angle)
{
    this->angle = angle;
    this->x += cos(qDegreesToRadians(this->angle))*step;
    this->y += -sin(qDegreesToRadians(this->angle))*step;
}

void Robot::scale(float factor)
{
    diameter *= factor;
    this->x *= factor;
    this->y *= factor;
}

void Robot::checkCollision(QVector<QGraphicsItem*> &items)
{
    for(int i = 0; i < items.size(); ++i){
        if(items.at(i)->collidesWithItem(circle))
            qDebug()<<"collide";
    }
}



