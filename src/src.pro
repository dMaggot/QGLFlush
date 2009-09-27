# -------------------------------------------------
# Project created by QtCreator 2009-09-24T14:52:29
# -------------------------------------------------
QT += opengl
TARGET = QGLFlush
TEMPLATE = app
SOURCES += main.cpp \
    qglflushwindow.cpp \
    qglflushvisualizer.cpp
HEADERS += qglflushwindow.h \
    qglflushvisualizer.h
FORMS += qglflushwindow.ui
INCLUDEPATH += /usr/include/Qsci /usr/include/python2.6
LIBS += -lqscintilla2 -lpython2.6
