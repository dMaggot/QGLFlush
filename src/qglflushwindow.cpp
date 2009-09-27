#include "qglflushwindow.h"
#include "ui_qglflushwindow.h"

#include <qscilexerpython.h>

QGLFlushWindow::QGLFlushWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::QGLFlushWindow)
{
    ui->setupUi(this);
    ui->codeEditor->setLexer(new QsciLexerPython());
}

QGLFlushWindow::~QGLFlushWindow()
{
    delete ui;
}

void QGLFlushWindow::on_updateButton_clicked()
{
    ui->widget->setCode(ui->codeEditor->text());
    ui->widget->updateGL();

    return;
}
