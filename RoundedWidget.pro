TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += roundedwidget \
           roundedwidgetplugin

roundedwidgetplugin.depends = roundedwidget
