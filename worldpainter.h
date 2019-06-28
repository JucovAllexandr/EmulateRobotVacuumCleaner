#ifndef WORLDPAINTER_H
#define WORLDPAINTER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QKeyEvent>
#include "robot.h"
class WorldPainter : public QWidget
{
    Q_OBJECT
public:
    explicit WorldPainter(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
QTimer timer;
Robot *robot;
int x=0,y=0;
};

#endif // WORLDPAINTER_H
