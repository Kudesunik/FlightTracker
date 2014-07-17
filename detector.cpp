#include "detector.h"
#include "flighttracker.h"

static int bufferArray[] = {1, 1, 300, 300};
static int coordArray[] = {1, 1, 800, 1, 800, 800, 1, 800};
static int check = 0;
static bool optimizationFlag = FALSE;

Detector::Detector() {
    
    cap = new VideoCapture("http://192.168.0.37:8080/video?x.mjpeg");
    //cap = new VideoCapture("VIDEO0009.mp4");
    
    img_object = imread("example3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    
    dWidth = cap -> get(CV_CAP_PROP_FRAME_WIDTH);
    dHeight = cap -> get(CV_CAP_PROP_FRAME_HEIGHT);
}

void Detector::refreshCap() {
    
    cap = new VideoCapture("http://192.168.0.37:8080/video?x.mjpeg");
    //cap = new VideoCapture("VIDEO0009.mp4");
    
    dWidth = cap -> get(CV_CAP_PROP_FRAME_WIDTH);
    dHeight = cap -> get(CV_CAP_PROP_FRAME_HEIGHT);
}

int* Detector::detectObject(Mat *frm, int midXA, int midYA) {
    
    Mat img_scene = *frm;
    
    if( !img_object.data || !img_scene.data ) { 
        string message = " Ошибка чтения ";
        return coordArray;
        cout << message << endl;
    }
    
    bufferArray[0] = midXA - 180;
    bufferArray[1] = midYA - 180;
    bufferArray[2] = midXA + 180;
    bufferArray[3] = midYA + 180;
    
    if (bufferArray[0] <= 0) {
        bufferArray[0] = 1;
    }
    if (bufferArray[1] <= 0) {
        bufferArray[1] = 1;
    }
    if ((bufferArray[2] + bufferArray[0]) >= img_scene.cols) {
        bufferArray[2] = img_scene.cols - bufferArray[0] - 1;
    }
    if ((bufferArray[3] + bufferArray[1]) >= img_scene.rows) {
        bufferArray[3] = img_scene.rows - bufferArray[1] - 1;
    }
    
    if (check == 10) {
        
        coordArray[0] = 1;
        coordArray[1] = 1;
        coordArray[2] = img_scene.cols - 1;
        coordArray[3] = 1;
        coordArray[4] = img_scene.cols - 1;
        coordArray[5] = img_scene.rows - 1;
        coordArray[6] = 1;
        coordArray[7] = img_scene.rows - 1;
        
        bufferArray[0] = 1;
        bufferArray[1] = 1;
        bufferArray[2] = img_scene.cols - 1;
        bufferArray[3] = img_scene.rows - 1;
        
        check = 0;
    }
    
    check++;
    
    if (!optimizationFlag) {
        bufferArray[0] = 0;
        bufferArray[1] = 0;
        bufferArray[2] = 0;
        bufferArray[3] = 0;
    }
    else {
        img_scene = (*frm)(Rect(bufferArray[0], bufferArray[1], bufferArray[2], bufferArray[3]));
    }
    
    imshow( "Good Matches & Object detection", img_scene );
        
    int minHessian = 800;
        
    SurfFeatureDetector detector(minHessian);
        
    std::vector<KeyPoint> keypoints_object, keypoints_scene;

    detector.detect( img_object, keypoints_object );
    detector.detect( img_scene, keypoints_scene );
            
    SurfDescriptorExtractor extractor;

    Mat descriptors_object, descriptors_scene;

    extractor.compute( img_object, keypoints_object, descriptors_object );
    extractor.compute( img_scene, keypoints_scene, descriptors_scene );
            
    FlannBasedMatcher matcher;
    vector< DMatch > matches;
    
    if (descriptors_object.empty()) {
        return coordArray;
    }
    
    if (descriptors_scene.empty()) {
        return coordArray;
    }
    
    matcher.match( descriptors_object, descriptors_scene, matches );

    double max_dist = 0; double min_dist = 100;
    for( int i = 0; i < descriptors_object.rows; i++ ) { 
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
    
    vector< DMatch > good_matches;
    
    for( int i = 0; i < descriptors_object.rows; i++ ) { 
        if( matches[i].distance < 6 * min_dist ) { 
            good_matches.push_back( matches[i]); 
        }
    }  
    
    vector<Point2f> obj;
    vector<Point2f> scene;
    
    for( int i = 0; i < good_matches.size(); i++ ) {
        obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt ); 
    }
    
    Mat H = findHomography(obj, scene, CV_RANSAC);
            
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
    obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
    std::vector<Point2f> scene_corners(4);

    perspectiveTransform( obj_corners, scene_corners, H);
    
    int diagLengthX1 = abs(scene_corners[2].x - scene_corners[0].x);
    int diagLengthY1 = abs(scene_corners[2].y - scene_corners[0].y);
    int diagLengthX2 = abs(scene_corners[1].x - scene_corners[3].x);
    int diagLengthY2 = abs(scene_corners[3].y - scene_corners[1].y);
    
    if (diagLengthX1 > 20 && diagLengthX2 > 20 && diagLengthY1 > 20 && diagLengthY2 > 20 &&
         diagLengthX1 < 300 && diagLengthX2 < 300 && diagLengthY1 < 300 && diagLengthY2 < 300) {
            coordArray[0] = static_cast<int>(scene_corners[0].x + bufferArray[0]);
            coordArray[1] = static_cast<int>(scene_corners[0].y + bufferArray[1]);
            coordArray[2] = static_cast<int>(scene_corners[1].x + bufferArray[0]);
            coordArray[3] = static_cast<int>(scene_corners[1].y + + bufferArray[1]);
            coordArray[4] = static_cast<int>(scene_corners[2].x + bufferArray[0]);
            coordArray[5] = static_cast<int>(scene_corners[2].y + bufferArray[1]);
            coordArray[6] = static_cast<int>(scene_corners[3].x + + bufferArray[0]);
            coordArray[7] = static_cast<int>(scene_corners[3].y + + bufferArray[1]);
            check = 0;
    }
    
    return coordArray;
}