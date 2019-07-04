#include "world.h"

World::World(QWidget *parent):
    QWidget (parent)
{
    drawRect.setText("Draw rectangle");
    drawEllipse.setText("Draw ellipse");

    QVBoxLayout *main_lyt = new QVBoxLayout();
    QHBoxLayout *scale_lyt = new QHBoxLayout();
    QLabel *lbl =new QLabel("Set size of map in meters width/height");
    sb_map_w.setMinimum(1);
    sb_map_h.setMinimum(1);
    mapSize.setWidth(100);
    mapSize.setHeight(100);
    scale_lyt->addWidget(lbl);
    scale_lyt->addWidget(&sb_map_w);
    scale_lyt->addWidget(&sb_map_h);
    scale_lyt->addWidget(&drawRect);
    scale_lyt->addWidget(&drawEllipse);

    scale_lyt->addStretch(1);
    main_lyt->addItem(scale_lyt);
    this->setLayout(main_lyt);
    worldPainter = new WorldPainter(this);
    main_lyt->addWidget(worldPainter);

    connect(&sb_map_w, SIGNAL(valueChanged(int)), this, SLOT(changeMapWidth(int)));
    connect(&sb_map_h, SIGNAL(valueChanged(int)), this, SLOT(changeMapHeight(int)));

    connect(&drawRect, &QPushButton::clicked, [=]{
        worldPainter->setDrawShape(DrawShape::Rectangle);
    });
    connect(&drawEllipse, &QPushButton::clicked, [=]{
        worldPainter->setDrawShape(DrawShape::Ellipse);
    });
}

void World::changeMapWidth(int w)
{
    mapSize.setWidth(w * 100);
    worldPainter->setMapSize(mapSize);
}

void World::changeMapHeight(int h)
{
    mapSize.setHeight(h * 100);
    worldPainter->setMapSize(mapSize);
}


