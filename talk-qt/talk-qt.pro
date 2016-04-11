QT += core
QT -= gui

CONFIG += c++11

TARGET = talk-qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    socketudp.cpp

HEADERS += \
    socketudp.hpp
