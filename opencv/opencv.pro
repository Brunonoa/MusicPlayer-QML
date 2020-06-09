QT -= gui

QT += qml quick

TEMPLATE = lib
DEFINES += OPENCV_LIBRARY

CONFIG += c++11

###################################
#       OPENCV LIBRARIES
###################################

LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lpthread
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_bgsegm
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_video
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_shape
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_photo
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_aruco
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_text
#LIBS += -L$$PWD/../../../../opt/b2qt/sdk-2.2.2/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_rgbd
#LIBS += -L$$PWD/../../../../opt/b2qt/sdk-2.2.2/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_plot
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_core
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_reg
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_dpm
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_dnn
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_ml
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_ts
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_highgui
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_imgproc
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_videoio
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_imgcodecs
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_ximgproc
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_datasets
#LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_optflow
LIBS += -L$$PWD/../../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_features2d
LIBS += -L$$PWD/../../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_xfeatures2d
LIBS += -L$$PWD/../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_calib3d
LIBS += -L$$PWD/../../../../../opt/b2qt/2.5.1.W/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/usr/lib/ -lopencv_flann

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    minipid.cpp \
    videocamera.cpp \
    videocamerapid.cpp \
    videocamerashower.cpp \
    videocameraworker.cpp

HEADERS += \
    minipid.h \
    opencv_global.h \
    videocamera.h \
    videocamerapid.h \
    videocamerashower.h \
    videocameraworker.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
