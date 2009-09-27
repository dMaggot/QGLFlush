#include "qglflushvisualizer.h"

#include <Python.h>

QGLFlushVisualizer::QGLFlushVisualizer(QWidget * w) :
        QGLWidget(w)
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

QGLFlushVisualizer::~QGLFlushVisualizer()
{
    Py_Finalize();
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

void QGLFlushVisualizer::paintGL()
{
    PyRun_SimpleString(code.toStdString().c_str());

    return;
}

void QGLFlushVisualizer::resizeGL(int w,int h)
{
    float aspectratio = (float)h/(float)w;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0*aspectratio, 100.0*aspectratio);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return;
}
void QGLFlushVisualizer::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    return;
}
