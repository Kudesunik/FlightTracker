#include "detector.h"

Detector::Detector() {
    
    cap = new VideoCapture(0);
    
    dWidth = cap -> get(CV_CAP_PROP_FRAME_WIDTH);
    dHeight = cap -> get(CV_CAP_PROP_FRAME_HEIGHT);
}

void Detector::refreshCap() {
    cap = new VideoCapture(0);
    
    dWidth = cap -> get(CV_CAP_PROP_FRAME_WIDTH);
    dHeight = cap -> get(CV_CAP_PROP_FRAME_HEIGHT);
}

/**
 * coordArray[0] = start_x;
 * coordArray[1] = start_y;
 * coordArray[2] = width;
 * coordArray[3] = height;
 */
int* Detector::getQuadCoords() {
    int coordArray[] = {0, 0, 0, 0};
    
    /* Setup coordArray code */
    
    /* End of setup */
    
    return coordArray;
}