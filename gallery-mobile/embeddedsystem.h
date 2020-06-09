#ifndef EMBEDDEDSYSTEM_H
#define EMBEDDEDSYSTEM_H

#include <QObject>

#include <unistd.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

class EmbeddedSystem : public QObject
{
    Q_OBJECT
public:
    explicit EmbeddedSystem(QObject *parent = nullptr);
    Q_INVOKABLE void shutdown() {system("shutdown -P now");}

signals:

public slots:
};

#endif // EMBEDDEDSYSTEM_H
