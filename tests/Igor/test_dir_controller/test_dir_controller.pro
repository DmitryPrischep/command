QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += ../../../dir_controller.h
SOURCES +=  tst_test_dir_controller.cpp \
            ../../../dir_controller.cpp
