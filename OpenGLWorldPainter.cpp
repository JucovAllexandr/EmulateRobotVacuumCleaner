#include "OpenGLWorldPainter.h"
#include <QDebug>
#include "helper.h"

OpenGLWorldPainter::OpenGLWorldPainter()
    : QOpenGLWidget()
{
    mvp.setToIdentity();
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(1);
}

OpenGLWorldPainter::OpenGLWorldPainter(QWidget *parent)
    : QOpenGLWidget(parent)
{
    mvp.setToIdentity();
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(1);
}

void OpenGLWorldPainter::setMapSize(QSize sz)
{
    map.setRect(0, 0, sz.width(), sz.height());
    fillGrid(sz.width(), sz.height(), 100);
}

void OpenGLWorldPainter::drawRectangle()
{
    makeCurrent();
    OpenGLRectangle *t = new OpenGLRectangle();
    t->init();
    t->setRect(0, 0, 0, 0);
    shapes.push_back(t);
    isDrawShape = true;
    doneCurrent();
}

void OpenGLWorldPainter::drawEllipse()
{
    makeCurrent();
    OpenGLEllipse *t = new OpenGLEllipse();
    t->init();
    t->setRect(0, 0, 0, 0);
    shapes.push_back(t);
    isDrawShape = true;
    doneCurrent();
}

void OpenGLWorldPainter::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    map.init();
    map.setPenColor(Qt::red);
    map.setBrushColor(Qt::white);
    map.setRect(0, 0, 1000, 1000);
    //transform.scale(0.4f);
    mvp.ortho(QRect(0, 0, width(), height()));

    grid.init();
    fillGrid(1000, 1000, 100);

    robot = new Robot (100, 100, 30);
    connect(&timer, &QTimer::timeout, [this](){this->update();});
    timer.start(30/1000);
}

void OpenGLWorldPainter::paintGL()
{
    MVP = transform * mvp;
    glClear(GL_COLOR_BUFFER_BIT);
    map.draw(MVP);
    grid.draw(MVP);
    robot->draw(MVP);

    for(int i = 0; i < shapes.size(); ++i){
        shapes[i]->draw(MVP);
    }
}

void OpenGLWorldPainter::resizeGL(int w, int h)
{
    mvp.setToIdentity();
    mvp.ortho(QRect(orthoX, orthoY, w, h));
}

void OpenGLWorldPainter::wheelEvent(QWheelEvent *event)
{
    scale += event->delta() / 600.f;
    /*transform.scale(scale, scale);*/
    mvp.setToIdentity();
    mvp.ortho(QRect(orthoX, orthoY, width() * scale, height() * scale));
}

void OpenGLWorldPainter::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftClicked && isDrawShape){
        //qDebug()<< "move " <<event->pos();
        QVector4D t = QVector4D(event->x() * scale + orthoX, event->y() * scale + orthoY, 0, 1);
        shapes.last()->setRect(startClick.x(), startClick.y(), t.x() - startClick.x(), t.y() - startClick.y());
        //shapes.last()->setRect(100 ,100 , 50, 50);
    }else if(isRightClicked){
        mvp.setToIdentity();
        orthoX = oldOrthoX + startRightClick.x() - event->x();
        orthoY = oldOrthoY + startRightClick.y() - event->y();
        mvp.ortho(QRect(orthoX, orthoY, width() * scale, height() * scale));
    }
}

void OpenGLWorldPainter::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton){
        isLeftClicked = true;
        //qDebug()<< "press " <<event->pos();
        startClick = QPoint(event->x() * scale + orthoX, event->y() * scale + orthoY);
    }else if(event->button() == Qt::MouseButton::RightButton){
        startRightClick = QPoint(event->x(), event->y());
        oldOrthoX = orthoX;
        oldOrthoY = orthoY;
        isRightClicked = true;
    }
}

void OpenGLWorldPainter::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton){
        isLeftClicked = false;
        isDrawShape = false;
    }else if(event->button() == Qt::MouseButton::RightButton){
        isRightClicked = false;
    }
}

void OpenGLWorldPainter::keyPressEvent(QKeyEvent *event)
{
    bool collision;

    if(event->key() == Qt::Key::Key_Up){
        collision = false;
        QVector<OpenGLShape*> buf = Helper::getAABBCollideShapes(shapes, robot->getRect());
        for(int i = 0; i < buf.size(); i++){
            if(robot->checkCollision(*buf[i])){
                collision = true;
                break;
            }
        }

        if(!collision){
            robot->move(1, angle);
        }

    }else if(event->key() == Qt::Key::Key_Down){
        robot->move(-1, angle);
    }else if(event->key() == Qt::Key::Key_Left){
        angle--;
        robot->move(0, angle);
    }else if(event->key() == Qt::Key::Key_Right){
        angle++;
        robot->move(0, angle);
    }
}

void OpenGLWorldPainter::fillGrid(int w, int h, int step)
{
    grid.erase();
    for(int i = 0; i < w; i+=step){
        grid.addLine(QVector2D(i, 0), QVector2D(i, h));
    }
    for(int j = 0; j < h; j+=step){

        grid.addLine(QVector2D(0, j), QVector2D(w, j));
    }
}
