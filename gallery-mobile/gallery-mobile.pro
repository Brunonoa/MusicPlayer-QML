TEMPLATE = app

QT += qml quick sql svg multimedia

CONFIG += c++11

message(Plugins: $$[QT_INSTALL_PLUGINS])

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/../bins

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

SOURCES += main.cpp \
    PictureImageProvider.cpp \
    embeddedsystem.cpp

RESOURCES += \
    res.qrc

LIBS            +=	-L$$OUT_PWD/../gallery-core/	-lgallery-core \
                        -L$$OUT_PWD/../playListModel/   -lplayListModel \
                        -L$$OUT_PWD/../SystemData/	-lSystemData \
                        -L$$OUT_PWD/../opencv/          -lopencv \
                        -L$$OUT_PWD/../Pinout/          -lPinout

LIBS            +=      -lasound -lgstreamer-1.0 -lpthread

INCLUDEPATH	+=	$$PWD/../gallery-core   $$PWD/../SystemData     $$PWD/../playListModel     $$PWD/../opencv      $$PWD/../Pinout
DEPENDPATH	+=	$$PWD/../gallery-core   $$PWD/../SystemData     $$PWD/../playListModel     $$PWD/../opencv      $$PWD/../Pinout

HEADERS += \
    PictureImageProvider.h \
    embeddedsystem.h \
    fonthelper.h \
    playlistmodel.h

target.path = /home/root
INSTALLS += target

DISTFILES += \
    camera/Opencv.qml \
    chart/Performances.qml \
    gallery/AlbumListPage.qml \
    gallery/AlbumPage.qml \
    gallery/InputDialog.qml \
    gallery/PicturePage.qml \
    main.qml \
    menu/Menu.qml \
    menu/PageTheme.qml \
    menu/Style.qml \
    menu/StyleDark.qml \
    menu/ToolBarTheme.qml \
    menu/qmldir \
    music/MusicController.qml \
    music/MusicPage.qml \
    music/PlayListBackground.qml \
    music/PlayListPage.qml \
    music/ScrollableText.qml \
    music/SliderBar.qml \
    music/privateFields.qml \
    time/Spinner.qml \
    time/TimeBackground.qml \
    time/TimePage.qml

unix:!macx: LIBS += -L$$PWD/../../../../../../../opt/b2qt/2.5.1.W/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi/usr/lib/plugins/audio/ -lqtaudio_alsa

INCLUDEPATH += $$PWD/../../../../../../../opt/b2qt/2.5.1.W/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi/usr/lib/plugins/audio
DEPENDPATH += $$PWD/../../../../../../../opt/b2qt/2.5.1.W/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi/usr/lib/plugins/audio
