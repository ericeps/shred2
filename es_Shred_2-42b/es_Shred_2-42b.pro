# qmake -o Makefile es_Shred.pro	# Generates a Makefile
# qmake -spec macx-xcode es_Shred.pro	# XCode Project
# qmake -tp vc es_Shred.pro		# visual studio project
######################################################################
######################################################################

TEMPLATE = app
CONFIG += qt debug
TARGET = 
DESTDIR = es_build
DEPENDPATH += .
INCLUDEPATH += . \
		src \
		src/both \
		src/SP \
		src/MP \
		src/UI


# Input
HEADERS +=	src/defs.h \
		src/physDefs.h \
		src/windefs.h \
		src/angleFuncs.h \
		src/MP/netdefs.h \
		src/MP/es_sequence.h \
		src/MP/es_MPgame.h \
		src/MP/es_players.h \
		src/MP/es_net.h \
		src/MP/es_client.h \
		src/MP/es_reliUdp.h \
		src/MP/es_pInfo.h \
		src/MP/es_server.h \
		src/MP/es_reliUdpServer.h \
		src/SP/es_SPgame.h \
		src/SP/enemyDefs.h \
		src/SP/es_baseEnem.h \
		src/SP/es_lookout.h \
		src/SP/es_chaser.h \
		src/SP/es_enemies.h \
		src/both/es_basegame.h \
		src/both/es_key.h \
		src/both/es_weapons.h \
		src/both/es_world.h \
		src/both/es_avatar.h \
		src/both/es_pickupcon.h \
		src/both/es_actionTimer.h \
		src/both/es_control.h \
		src/both/es_gamework.h \
		src/both/es_collision.h \
		src/both/es_compose.h \
		src/both/es_draw.h \
		src/both/es_qtgl.h \
		src/UI/chooseGame.h \
		src/UI/es_mainwindow.h \
		src/UI/es_MPbegin.h \
		src/UI/es_SPbegin.h \
		src/UI/es_UINet.h \
		src/UI/es_MPSett.h \
		src/UI/es_SPSett.h \
		src/UI/es_UIStats.h \
		src/UI/es_UIChat.h


SOURCES +=	src/main.cpp \
		src/angleFuncs.cpp \
		src/MP/es_MPgame.cpp \
		src/MP/es_players.cpp \
		src/MP/es_net.cpp \
		src/MP/es_client.cpp \
		src/MP/es_reliUdp.cpp \
		src/MP/es_pInfo.cpp \
		src/MP/es_server.cpp \
		src/MP/es_reliUdpServer.cpp \
		src/SP/es_SPgame.cpp \
		src/SP/enemyDefs.cpp \
		src/SP/es_baseEnem.cpp \
		src/SP/es_lookout.cpp \
		src/SP/es_chaser.cpp \
		src/SP/es_enemies.cpp \
		src/both/es_basegame.cpp \
		src/both/es_key.cpp \
		src/both/es_weapons.cpp \
		src/both/es_world.cpp \
		src/both/es_avatar.cpp \
		src/both/es_pickupcon.cpp \
		src/both/es_actionTimer.cpp \
		src/both/es_control.cpp \
		src/both/es_gamework.cpp \
		src/both/es_collision.cpp \
		src/both/es_compose.cpp \
		src/both/es_draw.cpp \
		src/both/es_qtgl.cpp \
		src/UI/chooseGame.cpp \
		src/UI/es_mainwindow.cpp \
		src/UI/es_MPbegin.cpp \
		src/UI/es_SPbegin.cpp \
		src/UI/es_UINet.cpp \
		src/UI/es_MPSett.cpp \
		src/UI/es_SPSett.cpp \
		src/UI/es_UIStats.cpp \
		src/UI/es_UIChat.cpp



QT += opengl
QT += network