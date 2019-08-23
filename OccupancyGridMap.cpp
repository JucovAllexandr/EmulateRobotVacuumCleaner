#include "OccupancyGridMap.h"
#include <iostream>
#include <QtMath>
#include <QFileDialog>
void OccupancyGridMap::mapInit()
{
	std::cout << "OccupancyGridMap construct start" << std::endl;
	map.resize(mapHeight);
	zeroPoint.setX(mapHeight / 2);
	zeroPoint.setY(mapHeight / 2);
	for (int i = 0; i < map.size(); ++i) {
		map[i].resize(mapHeight);
		map[i].fill(0.5f);
	}
	map[zeroPoint.x()][zeroPoint.y()] = 0;

	prevPoint = zeroPoint;

	std::cout << "OccupancyGridMap construct end" << std::endl;
}

float OccupancyGridMap::probability(float logOdd)
{
	return log(logOdd / (1 - logOdd));
}

float OccupancyGridMap::logOdd(float pob)
{
	return 1.0f - (1.0f / (1.0f + exp(pob)));
}

void OccupancyGridMap::resizeMap()
{
	mapHeight += resizeFactor;
	map.resize(mapHeight);
	for (int i = 0; i < map.size(); ++i) {
		map[i].reserve(mapHeight);
	}
}

void OccupancyGridMap::drawCircle(int xc, int yc, int x, int y)
{
	map[xc + x][ yc + y] = 0;
	map[xc - x][ yc + y] = 0;
	map[xc + x][ yc - y] = 0;
	map[xc - x][ yc - y] = 0;
	map[xc + y][ yc + x] = 0;
	map[xc - y][ yc + x] = 0;
	map[xc + y][ yc - x] = 0;
	map[xc - y][yc - x] = 0;
}

void OccupancyGridMap::circleBres(int xc, int yc, int r)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	drawCircle(xc, yc, x, y);
	while (y >= x)
	{
		// for each pixel we will 
		// draw all eight pixels 

		x++;

		// check for decision parameter 
		// and correspondingly  
		// update d, x, y 
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		drawCircle(xc, yc, x, y);
	}
}

OccupancyGridMap::OccupancyGridMap()
{
	mapInit();
}

int OccupancyGridMap::getMapHeight()
{
	return mapHeight;
}

void OccupancyGridMap::addStep(float angle, float step, bool isFree)
{
	std::cout << "angle: " << angle << " step: " << step << std::endl;
	QPoint nextPoint;
	nextPoint.setX(qRound(cos(qDegreesToRadians(angle)) * step) + prevPoint.x());
	nextPoint.setY(qRound(-sin(qDegreesToRadians(angle)) * step) + prevPoint.y());
	std::cout << "x: "<< nextPoint.x()<<" y: "<< nextPoint.y()<<std::endl;
	//for(int i = -15; i <= 15; i++)
	drawLine(prevPoint.x(), prevPoint.y(), nextPoint.x(), nextPoint.y(), isFree);

	prevPoint = nextPoint;
}

QVector<QVector<float>>& OccupancyGridMap::getMap(int size)
{
	int half = size / 2;
	int colMin, colMax;
	int rowMax = prevPoint.x() + half, rowMin = prevPoint.x() - half;

	if (rowMax >= mapHeight) {
		rowMax = mapHeight - 1;
	}
	if (rowMin < 0) {
		rowMin = 0;
	}
	
	buf.resize(size);
	for (int row = rowMin, br = 0; row < rowMax; ++row, ++br) {
		colMin = prevPoint.y() - half;
		colMax = prevPoint.y() + half;

		if (colMax >= mapHeight) {
			colMax = mapHeight - 1;
		}
		if (colMin < 0) {
			colMin = 0;
		}
		for (int col = colMin, bc = 0; col < colMax; ++col, ++bc) {
			buf[br].resize(size);
			//std::cout << "row " << row << " col " << col << std::endl;
			buf[br][bc] = map[row][col];
		}
	}
	return buf;
}

QPoint OccupancyGridMap::getCurPos()
{
	return prevPoint;
}

void OccupancyGridMap::drawLine(int x1, int y1, int x2, int y2, float val)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	//
	if (val > 0.6) {
		map[x2][y2] = val;
	}
	else {
	for (int i = 0; i < 30; i++)
		circleBres(x2, y2, i);
	}
	while (x1 != x2 || y1 != y2)
	{
		if (val > 0.6) {
			map[x2][y2] = val;
		}
		else {
			for (int i = 0; i < 30; i++)
				circleBres(x1, y1, i);
		}
		const int error2 = error * 2;
		//
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void OccupancyGridMap::saveMap()
{
	QString fileName = QFileDialog::getSaveFileName(NULL, QObject::tr("Save File"),
		"",
		QObject::tr("Images (*.png *.xpm *.jpg)"));

	QPixmap  pixmap(mapHeight, mapHeight);
	int c;
	QColor color;
	QPainter painter;
	painter.begin(&pixmap);
	for (int row = 0; row < mapHeight; ++row) {
		for (int col = 0; col < mapHeight; ++col) {
				c = abs((255 * map.at(row).at(col)) - 255);
				color.setRgb(c, c, c);
				painter.setPen(color);
				painter.drawPoint(row, col);

		}
	}
	painter.end();

	pixmap.save(fileName);
}
