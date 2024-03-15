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
	
// renders shapes in window
void OpenGLWindow::setRenderAttributes(const vector<Point3D>& inVertices, const vector<double>& inColors, const vector<Point3D>& inControlVertices, 
	const vector<double>& inOffsetVertices, const vector<double>& inConnectingVertices, const vector<double>& inNormalVertices)
{
	mControlVertices.clear();
	mVertices.clear();
	mColors.clear();
	mOffsetVertices.clear();
	mConnectingVertices.clear();
	mNormalVertices.clear();

	for (size_t i = 0; i < inControlVertices.size(); i++)
	{
		mControlVertices.push_back(inControlVertices[i].x());
		mControlVertices.push_back(inControlVertices[i].y());
		mControlVertices.push_back(inControlVertices[i].z());
	}

	for (size_t i = 0; i < inVertices.size(); i++)
	{
		mVertices.push_back(inVertices[i].x());
		mVertices.push_back(inVertices[i].y());
		mVertices.push_back(inVertices[i].z());
	}

	mColors = inColors;
	mOffsetVertices = inOffsetVertices;
	mConnectingVertices = inConnectingVertices;
	mNormalVertices = inNormalVertices;
}

void OpenGLWindow::initializeGL()
{
	static const char* vertexShaderSource =
		/*"attribute highp vec4 posAttr;\n"
		"attribute lowp vec4 colAttr;\n"
		"varying lowp vec4 col;\n"
		"uniform highp mat4 matrix;\n"
		"void main() {\n"
		"   col = colAttr;\n"
		"   gl_PointSize = 10.0;\n"
		"   gl_Position = matrix * posAttr;\n"
		"}\n";*/

		"attribute highp vec4 posAttr;\n"
		"attribute lowp vec4 colAttr;\n"
		"attribute lowp vec3 norAttr;\n"
		"varying lowp vec4 col;\n"
		"varying vec3 vert;\n"
		"varying vec3 vertNormal;\n"
		"uniform highp mat4 projMatrix;\n"
		"uniform highp mat4 viewMatrix;\n"
		"uniform highp mat4 modelMatrix;\n"
		"uniform mat3 normalMatrix;\n"
		"void main() {\n"
		"   col = colAttr;\n"
		"   vert = posAttr.xyz;\n"
		"   vertNormal = normalMatrix * norAttr;\n"
		"   gl_Position = projMatrix * viewMatrix * modelMatrix * posAttr;\n"
		"}\n";

	static const char* fragmentShaderSource =
		/*"varying lowp vec4 col;\n"
		"void main() {\n"
		"   gl_FragColor = col;\n"
		"}\n";*/


		"varying lowp vec4 col;\n"
		"varying highp vec3 vert;\n"
		"varying highp vec3 vertNormal;\n"
		"uniform highp vec3 lightPos;\n"
		"void main() {\n"
		"   highp vec3 L = normalize(lightPos - vert);\n"
		"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
		"   highp vec3 color = vec3(col);\n"
		"   highp vec3 col1 = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
		"   gl_FragColor = vec4(col1, 1.0);\n"
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
	m_normAttr = mProgram->attributeLocation("norAttr");
	Q_ASSERT(m_normAttr != -1);
	m_modelMatrixUniform = mProgram->uniformLocation("modelMatrix");
	Q_ASSERT(m_modelMatrixUniform != -1);
	m_viewMatrixUniform = mProgram->uniformLocation("viewMatrix");
	Q_ASSERT(m_viewMatrixUniform != -1);
	m_projectionMatrixUniform = mProgram->uniformLocation("projMatrix");
	Q_ASSERT(m_projectionMatrixUniform != -1);
	m_normalMatrixUniform = mProgram->uniformLocation("normalMatrix");
	Q_ASSERT(m_normalMatrixUniform != -1);
	m_lightPosUniform = mProgram->uniformLocation("lightPos");
	Q_ASSERT(m_lightPosUniform != -1);
	
}

void OpenGLWindow::paintGL()
{
	glClearColor(1.5f, 0.75f, 1.75f, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mProgram->bind();
	glLineWidth(3.0f);

	//QMatrix4x4 matrix;
	//matrix.ortho(-100.0f * scaleFactor, 100.0f * scaleFactor, -100.0f * scaleFactor, 100.0f * scaleFactor, 0.00000000001f, 1000000.0f);
	//matrix.perspective(60.0 * scaleFactor, 4.0/3.0 * scaleFactor, 0.1, 100.0);

	//float d = 500.0f; // Adjust this value based on your camera setup
	//float fov = 2.0f * atan((100.0f * scaleFactor) / d) * 180.0f / M_PI;

	//float aspectRatio = (100.0f * scaleFactor) / (100.0f * scaleFactor);

	//matrix.perspective(fov, aspectRatio, 0.1, 10000.0);

	/*matrix.translate(0, 0, -4);
	matrix.rotate(rotationAngle);*/
	//matrix.scale(3.0f);

	/*mProgram->setUniformValue(m_matrixUniform, matrix);*/

	QMatrix4x4 modelMatrix;
	QMatrix4x4 translationMatrix;
	QMatrix4x4 scaleMatrix;
	QMatrix4x4 rotationMatrix;
	QMatrix4x4 viewMatrix;
	QMatrix4x4 projectionMatrix;
	QMatrix3x3 normalMatrix;
	QVector3D lightPos;


	lightPos = QVector3D(0.0f, 0.0f, 20.0f);
	projectionMatrix.ortho(-100.0f * scaleFactor, 100.0f * scaleFactor, -100.0f * scaleFactor, 100.0f * scaleFactor, 0.00000000001f, 1000000.0f);

	//projectionMatrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
	//projectionMatrix.ortho(-100.0f * scaleFactor, 100.0f * scaleFactor, -100.0f * scaleFactor, 100.0f * scaleFactor, 0.00000000001f, 1000000.0f);
	

	//float d = 500.0f; // Adjust this value based on your camera setup
	//float fov = 2.0f * atan((100.0f * scaleFactor) / d) * 180.0f / M_PI;

	//float aspectRatio = (100.0f * scaleFactor) / (100.0f * scaleFactor);

	//projectionMatrix.perspective(fov, aspectRatio, 0.1, 10000.0);
	
	translationMatrix.translate(0, 200, -400);
	scaleMatrix.scale(30.0);
	rotationMatrix.rotate(rotationAngle);

	modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;
	viewMatrix.setToIdentity();
	normalMatrix = (modelMatrix.normalMatrix()).transposed();
	normalMatrix = (modelMatrix.normalMatrix());


	mProgram->setUniformValue(m_modelMatrixUniform, modelMatrix);
	mProgram->setUniformValue(m_viewMatrixUniform, viewMatrix);
	mProgram->setUniformValue(m_projectionMatrixUniform, projectionMatrix);
	mProgram->setUniformValue(m_normalMatrixUniform, normalMatrix);
	mProgram->setUniformValue(m_lightPosUniform, lightPos);

	// Enable vertex attributes
	glEnableVertexAttribArray(m_posAttr);
	glEnableVertexAttribArray(m_colAttr);
	glEnableVertexAttribArray(m_normAttr);

	// draw original heart curve
	glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mVertices.data());
	glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mColors.data());
	glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, mNormalVertices.data());
	glDrawArrays(GL_LINE_LOOP, 0, mVertices.size() / 3);
	
	// draw the extruded heart curve
	glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mOffsetVertices.data());
	glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mColors.data());
	glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, mNormalVertices.data());
	glDrawArrays(GL_LINE_LOOP, 0, mOffsetVertices.size() / 3);
	
	// draw connecting triangles between original and offset curves
	glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mConnectingVertices.data());
	glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mColors.data());
	glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, mNormalVertices.data());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, mConnectingVertices.size() / 3);

	// Disable vertex attributes
	glDisableVertexAttribArray(m_posAttr);
	glDisableVertexAttribArray(m_colAttr);
	glDisableVertexAttribArray(m_normAttr);
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