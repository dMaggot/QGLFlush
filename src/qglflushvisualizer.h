#ifndef QGLFLUSHVISUALIZER_H
#define QGLFLUSHVISUALIZER_H

#include <QGLWidget>

class QGLFlushVisualizer : public QGLWidget
{
    Q_OBJECT

public:
    QGLFlushVisualizer(QWidget *);
    virtual ~QGLFlushVisualizer();
    QSize sizeHint() const;
    void setCode(QString);

protected:
    void paintGL();
    void resizeGL(int,int);
    void initializeGL();

private:
    QString code;
};

#endif // QGLFLUSHVISUALIZER_H
