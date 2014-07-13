#ifndef DETECTOR_H
#define	DETECTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class Detector {
    
public:
    Detector();
    
    VideoCapture *cap;
    
    int* getQuadCoords();
    void refreshCap();
    
    double dWidth;
    double dHeight;
    
};

#endif	/* DETECTOR_H */

