QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    view/mainwindow.cc \
    controller/controller.cc \
    model/maze_model.cc \
    model/cave_model.cc \
    model/maze_solver.cc \
    view/my_widget.cc \

HEADERS += \
    view/mainwindow.h \
    controller/controller.h \
    model/point.h \
    model/maze_model.h \
    model/maze_solver.h \
    model/cave_model.h \
    view/my_widget.h \

FORMS += \
    view/mainwindow.ui

INCLUDEPATH += \
    ./ \
    ./view \
    ./controller \
    ./model \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
