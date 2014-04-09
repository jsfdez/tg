TEMPLATE = app
TARGET = tg
INCLUDEPATH += .
CONFIG += console

QT =

# Input
HEADERS += binlog.h \
           constants.h \
           include.h \
           interface.h \
           LICENSE.h \
           loop.h \
           lua-tg.h \
           mtproto-client.h \
           mtproto-common.h \
           net.h \
           no-preview.h \
           queries.h \
           structures.h \
           telegram.h \
           tools.h \
           tree.h
SOURCES += binlog.c \
           interface.c \
           loop.c \
           lua-tg.c \
           main.c \
           mtproto-client.c \
           mtproto-common.c \
           net.c \
           queries.c \
           structures.c \
           tools.c
		   
HEADERS += wincompat.h
SOURCES += wincompat.c
HEADERS += wingetopt.h
SOURCES += wingetopt.c
SOURCES += getline.c

SOURCES += $$files(readline/*.c, false)

DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += USE_READLINE_STATIC

INCLUDEPATH += "3rdParty/include"
LIBS += "3rdParty/lib/x64/libeay32MDd.lib"
LIBS += "3rdParty/lib/x64/readlineD.lib"
LIBS += "3rdParty/lib/x64/zlib.lib"
LIBS +=  Ws2_32.lib
INCLUDEPATH += 3rdParty
INCLUDEPATH += 3rdParty/zlib/include
