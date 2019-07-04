#ifndef WORLD_H
#define WORLD_H

#include <QWidget>
#include "worldpainter.h"
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class World: public QWidget
{
    Q_OBJECT
    QPushButton drawRect;
    QPushButton drawEllipse;
    WorldPainter *worldPainter;
    QSpinBox sb_map_w;
    QSpinBox sb_map_h;
    QSize mapSize;
public:
    World(QWidget *parent = nullptr);
private slots:
    void changeMapWidth(int w);
    void changeMapHeight(int h);

};

#endif // WORLD_H
