#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "point3D.h"

using namespace std;
using namespace Geometry;

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
    {
        Q_OBJECT

    public:
        OpenGLWindow(const QColor & background, QMainWindow * parent);
        ~OpenGLWindow();

        void setRenderAttributes(const vector<Point3D>& inVertices, const vector<double>& inColor);

    protected:
        void paintGL() override;
        void initializeGL() override;

    private:
        void reset();
        void mouseMoveEvent(QMouseEvent* event);
        void wheelEvent(QWheelEvent* event);
        void zoomIn();
        void zoomOut();


    private:
        bool mAnimating = false;
        QOpenGLContext* mContext = nullptr;
        QOpenGLPaintDevice* mDevice = nullptr;

        QOpenGLShader* mVshader = nullptr;
        QOpenGLShader* mFshader = nullptr;
        QOpenGLShaderProgram* mProgram = nullptr;

        vector<double> mVertices;
        vector<double> mColors;
        QList<QVector3D> mNormals;
        QOpenGLBuffer mVbo;
        int mVertexAttr;
        int mNormalAttr;
        int mMatrixUniform;

        QColor mBackground;
        QMetaObject::Connection mContextWatchConnection;

        GLint m_posAttr = 0;
        GLint m_colAttr = 0;
        GLint m_matrixUniform = 0;

        QQuaternion rotationAngle;
        QPoint lastPos;
        float scaleFactor = 5;

        //int m_frame;

        //bool mShowDroplet = false;
        //bool mShowHeart = false;

    };
