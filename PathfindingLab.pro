#-------------------------------------------------
#
# Project created by QtCreator 2013-01-14T15:49:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathfindingLab
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    TileMap.cpp \
    TileMapFile.cpp \
    pathfindingproblem.cpp \
    ScenarioFile.cpp \
    Scenario.cpp \
    TaskItem.cpp \
    EuclideanDistanceFunction.cpp \
    VertexHash.cpp \
    TaskRunner.cpp \
    AbstractGraph.cpp \
    ClusterBoundPathfindingProblem.cpp \
    AbstractPathfindingProblem.cpp \
    DistanceFunctions.cpp \
    SearchManagement/SearchManager.cpp \
    SearchManagement/SearchWorker.cpp \
    Scene/QGraphicsTileMapScene.cpp \
    Scene/QGraphicsTileItem.cpp \
    Scene/QGraphicsNodeItem.cpp \
    Scene/QGraphicsMapView.cpp \
    Scene/QGraphicsEdgeItem.cpp \
    SearchManagement/AStarWorker.cpp \
    Wrappers/SearchAlgorithm.cpp \
    Wrappers/Problem.cpp \
    Wrappers/AStar.cpp

HEADERS  += mainwindow.h \
    TileMap.h \
    TileMapFile.h \
    pathfindingproblem.h \
    ScenarioFile.h \
    Scenario.h \
    TaskItem.h \
    InteractionHandler.h \
    Task.h \
    VertexHash.h \
    TaskRunner.h \
    DistanceFunctions.h \
    DDALineOfSight.hpp \
    AbstractGraph.h \
    ClusterBoundPathfindingProblem.h \
    AbstractPathfindingProblem.h \
    SearchManagement/SearchManager.h \
    SearchAlgorithmTypes.hpp \
    Scene/QGraphicsTileMapScene.h \
    Scene/QGraphicsTileItem.h \
    Scene/QGraphicsNodeItem.h \
    Scene/QGraphicsMapView.h \
    Scene/QGraphicsEdgeItem.h \
    SearchManagement/SearchWorker.h \
    SearchManagement/AStarWorker.h \
    Wrappers/SearchAlgorithm.h \
    Wrappers/Problem.h \
    Wrappers/AStar.h

FORMS    += mainwindow.ui

CONFIG += c++11

INCLUDEPATH += $$PWD/../GraphSearchLibrary/

INCLUDEPATH += $$PWD/Scene
INCLUDEPATH += $$PWD/SearchManagement

unix|win32: LIBS += -L$$PWD/../build-GraphLibrary-Desktop-Debug/ -lGraphLibrary

INCLUDEPATH += $$PWD/../GraphLibrary/src
DEPENDPATH += $$PWD/../GraphLibrary/src

win32: PRE_TARGETDEPS += $$PWD/../build-GraphLibrary-Desktop-Debug/GraphLibrary.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-GraphLibrary-Desktop-Debug/libGraphLibrary.a
