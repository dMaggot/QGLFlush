#ifndef QGLFLUSHWINDOW_H
#define QGLFLUSHWINDOW_H

#include <QtGui/QMainWindow>

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

protected slots:
    void on_updateButton_clicked();
};

#endif // QGLFLUSHWINDOW_H
