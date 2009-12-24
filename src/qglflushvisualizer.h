#ifndef QGLFLUSHVISUALIZER_H
#define QGLFLUSHVISUALIZER_H

#include <QGLWidget>

#include "spiral.h"

class QGLFlushVisualizer : public QGLWidget
{
    Q_OBJECT

public:
    QGLFlushVisualizer(QWidget *);
    virtual ~QGLFlushVisualizer();
    QSize sizeHint() const;
    void setCode(QString);
    void startFlush();
    bool isFlushing();

protected:
    void paintGL();
    void resizeGL(int,int);
    void initializeGL();

private:
    void setupPython();

    QString code;

    float flushing;
    float tick;

    QImage data;
    QImage dataClear;

    QColor clearColor;

    Spiral * spiral;
};

#endif // QGLFLUSHVISUALIZER_H
