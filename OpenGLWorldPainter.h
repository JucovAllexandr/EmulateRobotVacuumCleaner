#pragma once
#include <QOpenGLWidget>
#include "robot.h"
#include <QtOpenGL>
#include "openglrectangle.h"
#include "openglellipse.h"
#include "opengllines.h"
#include <QTimer>
#include <QMatrix4x4>

class OpenGLWorldPainter : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
QOpenGLContext *opengl_context;
QMatrix4x4 mvp;
QMatrix4x4 MVP;
QMatrix4x4 transform;
OpenGLRectangle map;
OpenGLLines grid;
QTimer timer;
QPoint startClick;
QPoint startRightClick;
QPoint moveMouse;
int orthoX = 0, orthoY = 0;
int oldOrthoX = 0, oldOrthoY = 0;
float scale = 1;
bool isDrawShape = false;
bool isLeftClicked = false;
bool isRightClicked = false;
QVector<OpenGLShape*> shapes;
Robot *robot;
float angle = 180;

public:
    OpenGLWorldPainter();
    OpenGLWorldPainter(QWidget *parent = nullptr);
    void setMapSize(QSize sz);
    void drawRectangle();
    void drawEllipse();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void fillGrid(int w, int h, int step);
};
