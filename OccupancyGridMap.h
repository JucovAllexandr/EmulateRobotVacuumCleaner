#pragma once
#include <QVector>
#include <QPixmap>
#include <QPainter>
class OccupancyGridMap
{
	QVector<QVector<float>> map;
	QPoint zeroPoint;
	QPoint prevPoint;

	int resizeFactor;
	int mapHeight = 5000;
	QVector<QVector<float>> buf;

private:
	void mapInit();
	float probability(float logOdd);
	float logOdd(float pob);
	void resizeMap();
	void drawCircle(int xc, int yc, int x, int y);
	void circleBres(int xc, int yc, int r);

public:
	OccupancyGridMap();
	int getMapHeight();
	void addStep(float angle, float step, bool isFree);
	QVector<QVector<float>>& getMap(int size);
	QPoint getCurPos();
	void drawLine(int x1, int y1, int x2, int y2, float val);
	void saveMap();
	
};

