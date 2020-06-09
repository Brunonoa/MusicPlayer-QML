#ifndef FONTHELPER_H
#define FONTHELPER_H

#include <QObject>
#include <QFont>

class FontHelper: public QObject{
    Q_OBJECT
public:
    using QObject::QObject;
    Q_INVOKABLE QFont changeStretchFont(const QFont & font, int factor){
        QFont fn(font);
        fn.setStretch(factor);
        return fn;
    }
};

#endif // FONTHELPER_H
