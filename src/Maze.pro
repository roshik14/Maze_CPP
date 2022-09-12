QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controller.cc \
    Model/elleralgorithm.cc \
    Model/facade.cc \
    Model/filemanager.cc \
    Model/cave_generator.cc \
    Model/Drawer/labyrinthdrawer.cc \
    Model/Drawer/drawer.cc \
    Model/Drawer/cavedrawer.cc \
    Model/WaveAlgorithm/walls_matrix_for_search.cc \
    Model/WaveAlgorithm/wave_algorithm_path_creator.cc \
    Model/WaveAlgorithm/wave_algorithm_path_restorer.cc \
    Model/WaveAlgorithm/searcher.cc \
    View/mainwindow.cc \
    main.cc

HEADERS += \
    useful_structs.h \
    coordinatepoints.h \
    Controller/controller.h \
    Model/elleralgorithm.h \
    Model/facade.h \
    Model/filemanager.h \
    Model/cave_generator.h \
    Model/Drawer/drawer.h \
    Model/WaveAlgorithm/walls_matrix_for_search.h \
    Model/WaveAlgorithm/searcher.h \
    View/mainwindow.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
