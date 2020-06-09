#ifndef VIDEOCAMERASHOWER_H
#define VIDEOCAMERASHOWER_H

#include <QObject>
#include <QImage>
#include <QTimer>
#include <QThread>
#include <QPixmap>
#include <QDebug>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

#include "opencv_global.h"

using namespace cv;
using namespace std;

class OPENCV_EXPORT videocameraShower : public QObject
{
    Q_OBJECT
    friend class Videocamera;

public:
    explicit videocameraShower();
    ~videocameraShower();

public slots:
    void readFrame();

signals:
    void resultReady(const QImage& m_image);
    void originalMat(const Mat& original_image);

private:
    Mat original_image;
    QImage m_image;
    VideoCapture cap;
    double t0;
};

#endif // VIDEOCAMERASHOWER_H
