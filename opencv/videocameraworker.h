#ifndef VIDEOCAMERAWORKER_H
#define VIDEOCAMERAWORKER_H

#include <QObject>
#include <QDebug>
#include <QImage>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

#include "opencv_global.h"

using namespace cv;
using namespace std;

class OPENCV_EXPORT videocameraWorker : public QObject
{
    Q_OBJECT
public:
    explicit videocameraWorker(QObject *parent = nullptr);

    vector<int> getMaxColorPicked() {return max_hsv;}
    void setMaxColorPicked(vector<int> hsv) {max_hsv = hsv;}

    void setThreshold(int threshold) {m_threshold = threshold;}
    int getThreshold() {return m_threshold;}

    vector<int> getMinColorPicked() {return min_hsv;}
    void setMinColorPicked(vector<int> hsv) {min_hsv = hsv;}

    void setColorThreshold(int threshold) {m_threshold = threshold;}
    int getColorThreshold() {return m_threshold;}

signals:
    void objectFound(int centerx, int centery, int width, int height);
    void contoursFound(const QImage& image);

public slots:
    void retrieveOriginalMat(const Mat& originale_image);

private:
    QImage m_image;
    vector<int> min_hsv{0,0,0};
    vector<int> max_hsv{0,0,0};
    int m_threshold;
};

#endif // VIDEOCAMERAWORKER_H
