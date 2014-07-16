#ifndef DETECTOR_H
#define	DETECTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <vector>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace std;
using namespace cv;

class Detector {
    
public:
    Detector();
    
    VideoCapture *cap;
    
    void refreshCap();
    int* detectObject(Mat *frm, int midXA, int midYA);
    
    double dWidth;
    double dHeight;
    
    Mat img_object;
    
};

#endif	/* DETECTOR_H */

