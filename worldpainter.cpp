#include "worldpainter.h"
#include <QDebug>

WorldPainter::WorldPainter(QWidget *parent) : QWidget(parent)
{
    connect(&timer,&QTimer::timeout,[this](){
        this->update();
    });

    robot = new Robot(x , y, 30);
    timer.start(1000/30);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(1);
    mapSize.setWidth(100);
    mapSize.setHeight(100);

}

void WorldPainter::setMapSize(QSize sz)
{
    mapSize = sz;
}

void WorldPainter::setDrawShape(DrawShape type)
{
    drawShape = type;
}

void WorldPainter::paintEvent(QPaintEvent *event)
{
    QPainter painter;

    painter.begin(this);

    painter.translate(startTranX - tranX, startTranY - tranY);
    painter.scale(scale, scale);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.fillRect(0, 0, mapSize.width(), mapSize.height(), Qt::white);
    painter.setPen(QPen(QBrush(Qt::red),2));
    painter.drawRect(0, 0, mapSize.width(), mapSize.height());
    painter.setPen(QPen(QBrush(Qt::black),2));

    if(isCanDrawShape){
        if(drawShape == DrawShape::Rectangle){
            painter.drawRect(shape1.x(), shape1.y(), shape2.x() - shape1.x(), shape2.y() - shape1.y());
        }
        else if(drawShape == DrawShape::Ellipse){
            painter.drawEllipse(shape1.x(), shape1.y(), shape2.x() - shape1.x(), shape2.y() - shape1.y());
        }
    }

    for(int i = 0; i < shapes.size(); ++i){
        shapes.at(i)->paint(&painter, &styleOption);
    }

    robot->draw(&painter);
    robot->move(x,y);
    robot->checkCollision(shapes);

    painter.end();

}

void WorldPainter::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Up)
        x++;
    else if(event->key() == Qt::Key::Key_Down)
        x--;
    else if(event->key() == Qt::Key::Key_Right)
    {
        if(y >= 360)
            y= 0;
        else
            y++;
    }
    else if(event->key() == Qt::Key::Key_Left)
    {
        if(y <= 0)
            y= 360;
        else
            y--;
    }
}

void WorldPainter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && isCanDrawShape)
    {
        isCanDrawShape = 0;
    }
}

void WorldPainter::wheelEvent(QWheelEvent *event)
{
    scale += event->delta() / 300.f;
}

void WorldPainter::mouseMoveEvent(QMouseEvent *event)
{
    if(isCanTranslate){
        tranX = event->x();
        tranY = event->y();
    }

    if(drawShape > 0){
        shape2.setX(event->x());
        shape2.setY(event->y());
    }
}

void WorldPainter::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MouseButton::RightButton){
        isCanTranslate = 1;
        setCursor(Qt::SizeAllCursor);
        startTranX = event->x();
        startTranY = event->y();
    }

    if(drawShape > 0 && !isCanDrawShape){
        isCanDrawShape = 1;
        shape1 = event->localPos().toPoint();
        shape2 = event->localPos().toPoint();
    }

}

void WorldPainter::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    isCanTranslate = 0;

    if(drawShape > 0 && isCanDrawShape){
        isCanDrawShape = 0;
        shape2 = event->localPos().toPoint();
        QGraphicsItem *item;
        if(drawShape == DrawShape::Ellipse){
            item = new QGraphicsEllipseItem(QRect(shape1, shape2));
            ((QGraphicsEllipseItem*)item)->setBrush(QBrush(Qt::black));
        }
        else if(drawShape == DrawShape::Rectangle){
            item = new QGraphicsRectItem(QRect(shape1, shape2));
            ((QGraphicsRectItem*)item)->setBrush(QBrush(Qt::black));
        }

        shapes.push_back(item);
        drawShape = DrawShape::None;
    }

}

