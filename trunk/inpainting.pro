# -------------------------------------------------
# Project created by QtCreator 2011-01-12T16:07:15
# -------------------------------------------------
TARGET = inpainting
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    cimage.cpp \
    dialog_util.cpp \
    ctschumperle.cpp \
    cmgvc.cpp
HEADERS += mainwindow.h \
    cimage.h \
    dialog_util.h \
    ctschumperle.h \
    cmgvc.h
FORMS += mainwindow.ui \
    dialog_util.ui
CONFIG += console
CONFIG += uitools
