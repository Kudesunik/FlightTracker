# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = FlightTracker
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += link_pkgconfig debug 
PKGCONFIG += opencv Qt3Support QtCLucene QtCore QtDBus QtDeclarative QtDesigner QtDesignerComponents QtGui QtHelp QtNetwork QtOpenGL QtScript QtScriptTools QtSql QtSvg QtTest QtUiTools QtWebKit QtXml QtXmlPatterns
QT = core gui widgets
SOURCES += detector.cpp flighttracker.cpp main.cpp
HEADERS += detector.h flighttracker.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/local/include/opencv2 
LIBS += -Wl,-rpath,/usr/local/include/opencv2 
