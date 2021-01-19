######################################################################
# Automatically generated by qmake (3.1) Wed Jun 17 09:38:22 2020
######################################################################

TEMPLATE = app
TARGET = FC_Server_ran
CONFIG += console c++11
INCLUDEPATH += .

QT += quick sql
#LIBS +=/usr/local/include/boost_1_72_0/stage/lib/libboost_thread.a
LIBS +=/usr/lib/libboost_thread.a
include(json/json.pri)


# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += fc_acceptor.h \
           Moments/fc_concretemoments.h \
           Moments/fc_observer.h \
           Moments/fc_subject.h \
           Moments/fc_viewer.h \
           fc_connection.h \
           fc_database.h \
           fc_db_proxy.h \
           fc_display.h \
           fc_header.h \
           fc_message.h \
           fc_message_handle.h \
           fc_server.h \
           fc_thread_pool.h

SOURCES += fc_acceptor.cpp \
           Moments/fc_concretemoments.cpp \
           Moments/fc_viewer.cpp \
           fc_connection.cpp \
           fc_database.cpp \
           fc_db_proxy.cpp \
           fc_display.cpp \
           fc_message.cpp \
           fc_message_handle.cpp \
           fc_server.cpp \
           fc_thread_pool.cpp \
           main.cpp

