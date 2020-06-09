#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T23:11:38
#
#-------------------------------------------------

QT += qml quick gui-private

CONFIG += plugin

TARGET = MockupVirtualKeyboard
TEMPLATE = lib

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.tsts.comps
#where the plugin is deployed locally
DESTDIR = $$PWD/../bins/com/tsts/comps

DEFINES += MOCKUPVIRTUALKEYBOARD_LIBRARY

SOURCES += mockupplatforminputcontextplugin.cpp \
    mockupinputcontext.cpp \
    mockupkeyeventdispatcher.cpp

HEADERS += mockupplatforminputcontextplugin.h\
        mockupvirtualkeyboard_global.h \
    mockupinputcontext.h \
    mockupkeyeventdispatcher.h

OTHER_FILES += \
    InputPanel.qml \
    KeyModel.qml \
    KeyButton.qml

RESOURCES += \
    mockupresources.qrc

DISTFILES += \
    qmldir

qmldir.files = qmldir
unix {
    installPath = /usr/lib/plugins/com/tsts/comps   #$$replace(uri, \\., /)##$$[QT_INSTALL_QML]
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
