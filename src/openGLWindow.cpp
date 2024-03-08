#include "stdafx.h"
#include "openGLWindow.h"
#include "bezier.h"
#include "heart3D.h"
#include "droplet3D.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>


OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;  
    mVbo.destroy();
    doneCurrent();
}

void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_PointSize = 10.0;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    rotationAngle = QQuaternion::fromAxisAndAngle(180.0f, 0.0f, 1.0f, 0.0f);

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void OpenGLWindow::paintGL()
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mProgram->bind();
    glLineWidth(3.0f);

    QMatrix4x4 matrix; 
    matrix.ortho(-100.0f * scaleFactor, 100.0f * scaleFactor, -100.0f * scaleFactor, 100.0f * scaleFactor, 0.00000000001f, 1000000.0f);
    matrix.translate(0, 0, -15);
    matrix.rotate(rotationAngle);
    matrix.scale(50.0f);
 
    mProgram->setUniformValue(m_matrixUniform, matrix);   

    if (mShowDroplet)
    {
        renderDroplet();
    }   
    else if (mShowHeart)
    {
        renderHeart();
    }    
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
    {
        zoomOut();
    }
    else
    {
        zoomIn();
    }
}

void OpenGLWindow::zoomIn()
{
    scaleFactor *= 1.1f;
    update();
}

void OpenGLWindow::zoomOut()
{
    scaleFactor /= 1.1f;
    update();
}


void OpenGLWindow::toggleDropletVisibility()
{
    mShowDroplet = !mShowDroplet;
}

void OpenGLWindow::toggleHeartVisibility()
{
    mShowHeart = !mShowHeart;
}


void OpenGLWindow::renderHeart()
{
    Geometry::Heart3D heart;
    heart.draw();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, heart.heartCoordinates().data());

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, heart.heartColors().data());

    glDrawArrays(GL_LINE_LOOP, 0, heart.heartCoordinates().size() / 3);

    glDisableVertexAttribArray(m_posAttr);
    glDisableVertexAttribArray(m_colAttr);
   
    /* FOR POINTS COLOR */
    
    //QVector<double> heartPoints;  
    //QVector<double> heartPointsColors;

    // for (const auto& point : heart.heartPoints())
    //{
    //    heartPoints.push_back(point.x());
    //    heartPoints.push_back(point.y());
    //    heartPoints.push_back(point.z());

    //    heartPointsColors.push_back(1.0); // Red
    //    heartPointsColors.push_back(0.0); // Green
    //    heartPointsColors.push_back(0.0); // Blue
    //}

    //glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, heartPoints.data());
    //glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, heartPointsColors.data());

    //glEnableVertexAttribArray(m_posAttr);
    //glEnableVertexAttribArray(m_colAttr);
    //glEnable(GL_PROGRAM_POINT_SIZE);

    //glDrawArrays(GL_POINTS, 0, heartPoints.size());

    //glDisableVertexAttribArray(m_posAttr);
    //glDisableVertexAttribArray(m_colAttr);
    //glDisable(GL_PROGRAM_POINT_SIZE);

    mProgram->release();
}

void OpenGLWindow::renderDroplet()
{
    Geometry::Droplet3D droplet;
    droplet.draw();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, droplet.dropletCoordinates().data());

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, droplet.dropletColors().data());

    glDrawArrays(GL_LINE_LOOP, 0, droplet.dropletCoordinates().size() / 3);

    glDisableVertexAttribArray(m_posAttr);
    glDisableVertexAttribArray(m_colAttr);

    /* FOR POINTS COLOR */

    //QVector<double> heartPoints;  
    //QVector<double> heartPointsColors;

    // for (const auto& point : heart.heartPoints())
    //{
    //    heartPoints.push_back(point.x());
    //    heartPoints.push_back(point.y());
    //    heartPoints.push_back(point.z());

    //    heartPointsColors.push_back(1.0); // Red
    //    heartPointsColors.push_back(0.0); // Green
    //    heartPointsColors.push_back(0.0); // Blue
    //}

    //glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, heartPoints.data());
    //glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, heartPointsColors.data());

    //glEnableVertexAttribArray(m_posAttr);
    //glEnableVertexAttribArray(m_colAttr);
    //glEnable(GL_PROGRAM_POINT_SIZE);

    //glDrawArrays(GL_POINTS, 0, heartPoints.size());

    //glDisableVertexAttribArray(m_posAttr);
    //glDisableVertexAttribArray(m_colAttr);
    //glDisable(GL_PROGRAM_POINT_SIZE);

    mProgram->release();
}
