#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include <QLibraryInfo>
#include <QtMultimedia/QMediaPlaylist>
#include <QDebug>
#include <QFont>

#include "pwm.h"
#include "videocamera.h"
#include "volumelevel.h"
#include "playlistmodel.h"
#include "albummodel.h"
#include "picturemodel.h"
#include "systemcore.h"
#include "fonthelper.h"
#include "PictureImageProvider.h"
#include "embeddedsystem.h"

using namespace exploringRPi;

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Q_DECLARE_METATYPE(Mat)
Q_DECLARE_METATYPE(QMediaPlaylist*)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Registro il tipo definito Videocamera
    qmlRegisterType<VideoCamera>("VideocameraLib", 1, 0, "Videocamera");
    // Registro il tipo definito Pwm
    qmlRegisterType<PWM>("PwmLib", 1, 0, "Pwm");
    // Registro il tipo definito Pwm
    //qmlRegisterType<VolumeLevel>("VolumeLevelLib", 1, 0, "Volume");

    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());
    app.setApplicationVersion("0.0.1");

    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    app.setOrganizationName("davideTech");
    app.setOrganizationDomain("World");

    //qDebug()<<QLibraryInfo::location(QLibraryInfo::PluginsPath);
    //qDebug()<<QCoreApplication::applicationDirPath();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
           return -1;

    AlbumModel albumModel;
    PictureModel pictureModel(albumModel);
    PlayListModel playlistModel("/home/root");
    Systemcore::instance().init();
    FontHelper helper;
    VolumeLevel volume;
    EmbeddedSystem systemCalls;

    context->setContextProperty("thumbnailSize", PictureImageProvider::THUMBNAIL_SIZE.width());
    context->setContextProperty("albumModel", &albumModel);
    context->setContextProperty("pictureModel", &pictureModel);
    context->setContextProperty("playlistModel", &playlistModel);
    context->setContextProperty("systemcore", &Systemcore::instance());
    context->setContextProperty("fontHelper", &helper);
    context->setContextProperty("volumeMeter", &volume);
    context->setContextProperty("systemCall", &systemCalls);

    engine.addImageProvider("pictures", new PictureImageProvider(&pictureModel));

    return app.exec();
}