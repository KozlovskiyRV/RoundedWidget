TEMPLATE = lib
CONFIG += plugin qtuiplugin debug_and_release
QT += widgets designer

TARGET = roundedwidgetplugin

HEADERS += roundedwidgetplugin.h
SOURCES += roundedwidgetplugin.cpp
RESOURCES += icons.qrc

INCLUDEPATH += ../roundedwidget
LIBS += -L$$OUT_PWD/../roundedwidget/release -lroundedwidget

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
