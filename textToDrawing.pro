#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T22:00:36
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = textToDrawing
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
LIBS += -ldxflib
SOURCES += main.cpp \
    wall.cpp

HEADERS += \
    wall.h
