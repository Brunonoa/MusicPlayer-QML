#include "videocameraworker.h"

videocameraWorker::videocameraWorker(QObject *parent) :
    QObject(parent),
    m_threshold(20)    
{ }

int getMaxAreaContourId(vector<vector<Point>> contours) {
    double maxArea = 0;
    int maxAreaContourId = -1;
    for (int j = 0; j < static_cast<int>(contours.size()); j++) {
        double newArea = cv::contourArea(contours.at(static_cast<unsigned int>(j)));
        if (newArea > maxArea) {
            maxArea = newArea;
            maxAreaContourId = j;
        } // End if
    } // End for
    return maxAreaContourId;
}

void videocameraWorker::retrieveOriginalMat(const Mat& originale_image)
{
    Scalar lowerLimit = Scalar(qBound(0, min_hsv.at(0) - m_threshold, 255),
                               qBound(0, min_hsv.at(1) - m_threshold, 255),
                               qBound(0, min_hsv.at(2) - 4*m_threshold, 255));
    Scalar upperLimit = Scalar(qBound(0, max_hsv.at(0) + m_threshold, 255),
                               qBound(0, max_hsv.at(1) + m_threshold, 255),
                               qBound(0, max_hsv.at(2) + 4*m_threshold, 255));

    Mat frame, hsv;
    cvtColor(originale_image, hsv, COLOR_BGR2HSV);
    // construct a mask for the color "green", then perform a series of dilations and
    // erosions to remove any small blobs left in the mask
    Mat mask;
    vector<vector<Point>> contours;
    inRange(hsv, lowerLimit, upperLimit, mask);
    erode(mask, mask, 2);
    dilate(mask, mask, 2);
    // find contours in the mask and initialize the current (x, y) center of the ball
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //only proceed if at least one contour was found
    if(contours.size() > 0)
    {
        // find the largest contour in the mask, then use it to compute the minimum enclosing circle and centroid
        int id = getMaxAreaContourId(contours);
        if((id >= 0) & (id < static_cast<int>(contours.size())))
        {
            Scalar colourContours = Scalar(250,128,114);
            drawContours(originale_image, contours, id, colourContours);

            // only proceed if the radius meets a minimum size
            vector<Point> perimeter = contours.at(static_cast<unsigned int>(id));
            Rect rect = boundingRect(perimeter);//minAreaRect(perimeter);
            if(rect.area() > 400)
                emit objectFound(rect.x, rect.y, rect.width, rect.height);
            else
                emit objectFound(0, 0, 0, 0);
        }
        else
            emit objectFound(0, 0, 0, 0);
    }
    else
        emit objectFound(0, 0, 0, 0);

    // Pass the camera frame for conversion to QImage
    m_image = QImage(static_cast<uchar*>(originale_image.data), originale_image.cols, originale_image.rows,
                     static_cast<int>(originale_image.step), QImage::Format_RGB888);
    emit contoursFound(m_image);
}

