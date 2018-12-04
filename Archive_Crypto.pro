#-------------------------------------------------
#
# Project created by QtCreator 2018-10-24T18:38:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Archive_Crypto
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS += -std=c++17
#QMAKE_LFLAGS += -lstdc++fs
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++1z

SOURCES += \
        main.cpp \
        main_form.cpp \
    dir_controller.cpp \
    compressor/LZW.cpp \
    compressor/Selector.cpp \
    compressor/integrations_test/FileInfo.cpp \
    compressor/integrations_test/RW_Interface.cpp \
    compressor/integrations_test/RW_Liner.cpp \
    compressor/integrations_test/Test_Compress_And_Decompress.cpp \
   # crypto/key.cpp \
   # crypto/aes.cpp
    passworddialog.cpp


HEADERS += \
        main_form.h \
    dir_controller.h \
    compressor/Coder.hpp \
    compressor/LZW.hpp \
    compressor/Node.hpp \
    compressor/Selector.hpp \
    compressor/integrations_test/FileInfo.h \
    compressor/integrations_test/RW_Interface.h \
    compressor/integrations_test/RW_Liner.h \
    compressor/integrations_test/Test_Compress_And_Decompress.h \
  #  crypto/key.h \
  # crypto/aes.h
    passworddialog.h

FORMS += \
        main_form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

BOOST_ROOT = /usr/local/boost-1.68.0
INCLUDEPATH += -I $${BOOST_ROOT}/include
LIBS += -L $${BOOST_ROOT}/lib -lboost_system -lboost_filesystem

