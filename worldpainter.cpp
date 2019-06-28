#include "worldpainter.h"

WorldPainter::WorldPainter(QWidget *parent) : QWidget(parent)
{
    connect(&timer,&QTimer::timeout,[this](){
        this->update();
    });
    robot = new Robot(x,y);
    timer.start(1000/30);
    setFocusPolicy(Qt::ClickFocus);
}

void WorldPainter::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.fillRect(event->rect(),Qt::white);
    painter.setPen(QPen(QBrush(Qt::red),2));
    painter.drawRect(event->rect());
    //painter.setBrush(Qt::black);
    robot->draw(&painter);
    robot->move(x,y);
    //x++;
    //y++;
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
  //  x = 0;
}
