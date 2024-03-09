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

using namespace Geometry;
using namespace std;

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

void OpenGLWindow::setRenderAttributes(const vector<Point3D>& inVertices, const vector<double>& inColors)
{
	mVertices.clear();
	mColors.clear();

	for (size_t i = 0; i < inVertices.size(); i++)
	{
		mVertices.push_back(inVertices[i].x());
		mVertices.push_back(inVertices[i].y());
		mVertices.push_back(inVertices[i].z());
	}

	//for (size_t i = 0; i < inColors.size(); i++)
	//{
	//	mColors.push_back(inColors[i]);
	//	/*mColors.push_back(inColors[i].y());
	//	mColors.push_back(inColors[i].z());*/
	//}

	mColors = inColors;
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
	matrix.scale(3.0f);

	mProgram->setUniformValue(m_matrixUniform, matrix);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mVertices.data());

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mColors.data());

	glDrawArrays(GL_LINE_LOOP, 0, mVertices.size() / 3);

	glDisableVertexAttribArray(m_posAttr);
	glDisableVertexAttribArray(m_colAttr);
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