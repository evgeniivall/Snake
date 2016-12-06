QT += core
QT -= gui

CONFIG += c++11

TARGET = Snake
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    source.cpp \
    snake.cpp

HEADERS += \
    snake.h
