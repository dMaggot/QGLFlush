#ifndef QGLFLUSHWINDOW_H
#define QGLFLUSHWINDOW_H

#include <QtGui/QMainWindow>

#include <QTimer>

namespace Ui
{
    class QGLFlushWindow;
}

class QGLFlushWindow : public QMainWindow
{
    Q_OBJECT

public:
    QGLFlushWindow(QWidget *parent = 0);
    ~QGLFlushWindow();

private:
    Ui::QGLFlushWindow *ui;
    QTimer updaterTimer;

protected slots:
    void updater();
    void on_updateButton_clicked();
    void on_glFlushButton_clicked();
};

#endif // QGLFLUSHWINDOW_H
