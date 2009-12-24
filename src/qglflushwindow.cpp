#include "qglflushwindow.h"
#include "ui_qglflushwindow.h"

#include <qscilexerpython.h>

#include <QDebug>

QGLFlushWindow::QGLFlushWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::QGLFlushWindow)
{
    ui->setupUi(this);
    ui->codeEditor->setLexer(new QsciLexerPython());

    updaterTimer.setInterval(0);
    connect(&updaterTimer, SIGNAL(timeout()), this, SLOT(updater()));
    updaterTimer.start();
}

QGLFlushWindow::~QGLFlushWindow()
{
    delete ui;
}

void QGLFlushWindow::updater()
{
    if(ui->widget->isFlushing())
    {
        ui->glFlushButton->setEnabled(false);
        ui->widget->updateGL();
    }
    else if(!ui->glFlushButton->isEnabled())
        ui->glFlushButton->setEnabled(true);
}

void QGLFlushWindow::on_updateButton_clicked()
{
    ui->widget->setCode(ui->codeEditor->text());
    ui->widget->updateGL();

    return;
}

void QGLFlushWindow::on_glFlushButton_clicked()
{
    ui->widget->startFlush();

    return;
}
