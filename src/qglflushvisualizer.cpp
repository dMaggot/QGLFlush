#include "qglflushvisualizer.h"

#include <Python.h>

#include <QDebug>

#include "logarithmicspiral.h"

QGLFlushVisualizer::QGLFlushVisualizer(QWidget * w) :
        QGLWidget(w), dataClear(QSize(width(),height()), QImage::Format_ARGB32)
{
    setupPython();

    flushing = false;

    spiral = new LogarithmicSpiral(3.0f,0.3f);
}

QGLFlushVisualizer::~QGLFlushVisualizer()
{
    Py_Finalize();
}

void QGLFlushVisualizer::setupPython()
{
    QVector<PyObject *> openGLModules;

    Py_Initialize();

    PyObject * mainModule = PyImport_AddModule("__main__");

    openGLModules.push_back(PyImport_ImportModule("OpenGL.GL"));
    openGLModules.push_back(PyImport_ImportModule("OpenGL.GLU"));
    openGLModules.push_back(PyImport_ImportModule("OpenGL.GLUT"));

    for(QVector<PyObject *>::iterator i = openGLModules.begin(); i < openGLModules.end(); i++)
    {
        PyObject * moduleAttributes = PyObject_Dir(*i);

        Py_ssize_t pos = 0;
        Py_ssize_t attrSize = PyList_Size(moduleAttributes);

        while (pos < attrSize)
        {
            PyObject * attrValue = PyList_GetItem(moduleAttributes, pos);

            PyModule_AddObject(mainModule, PyString_AsString(attrValue), PyObject_GetAttr(*i,attrValue));
            pos++;
        }
    }
}

QSize QGLFlushVisualizer::sizeHint() const
{
    return QSize(800,600);
}

void QGLFlushVisualizer::setCode(QString _code)
{
    code = _code;

    return;
}

void QGLFlushVisualizer::startFlush()
{
    flushing = true;

    return;
}

bool QGLFlushVisualizer::isFlushing()
{
    return flushing;
}

void QGLFlushVisualizer::paintGL()
{
    if(!flushing)
    {
        PyRun_SimpleString(code.toStdString().c_str());
        data = grabFrameBuffer();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        QImage dataCopy = dataClear;

        flushing = false;

        for (int i = 0; i < dataCopy.width(); i++)
        {
            for (int j = 0; j < dataCopy.height(); j++)
            {
                if (data.pixel(i,j) != clearColor.rgb())
                {
                    int x = i - data.width()/2;
                    int y = j - data.height()/2;

                    spiral->transform(x, y, tick);

                    x += dataCopy.width()/2;
                    y += dataCopy.height()/2;

                    if (dataCopy.rect().contains(x,y))
                    {
                        if(!QRect(width()/2-1,height()/2-1,3,3).contains(x,y))
                        {
                            dataCopy.setPixel(x,y, data.pixel(i,j));
                            flushing = true;
                        }
                    }
                }
            }
        }

        GLuint test = bindTexture(dataCopy.transformed(QMatrix().scale(1,-1)));
        drawTexture(QRectF(QPointF(-100.0f,-100.0f), QSizeF(200.0f,200.0f)), test);

        tick += 1.0e-6f;
    }

    return;
}

void QGLFlushVisualizer::resizeGL(int w,int h)
{
    float aspectratio = (float)h/(float)w;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-100.0, 100.0, -100.0*aspectratio, 100.0*aspectratio);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    dataClear = dataClear.scaled(QSize(w,h));

    for (int i = 0; i < width(); i++)
        for (int j = 0; j < height(); j++)
            dataClear.setPixel(QPoint(i,j), clearColor.rgb());

    return;
}

void QGLFlushVisualizer::initializeGL()
{
    GLfloat tmpClearColor[4];

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glGetFloatv(GL_COLOR_CLEAR_VALUE, tmpClearColor);

    clearColor.setRedF(tmpClearColor[0]);
    clearColor.setGreenF(tmpClearColor[1]);
    clearColor.setBlueF(tmpClearColor[2]);
    clearColor.setAlphaF(tmpClearColor[3]);

    return;
}
