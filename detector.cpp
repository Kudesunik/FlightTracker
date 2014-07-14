#include "detector.h"

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

/**
 * coordArray[0] = start_x;
 * coordArray[1] = start_y;
 * coordArray[2] = width;
 * coordArray[3] = height;
 */
int* Detector::detectObject(Mat *frm) {
    
    int coordArray[] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    Mat img_scene = *frm;

    if( !img_object.data || !img_scene.data ) { 
        string message = " Ошибка чтения ";
        cout << message << endl;
    }
        
    int minHessian = 600;
        
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
    matcher.match( descriptors_object, descriptors_scene, matches );

    double max_dist = 0; double min_dist = 100;
    for( int i = 0; i < descriptors_object.rows; i++ ) { 
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
    
    vector< DMatch > good_matches;
    
    for( int i = 0; i < descriptors_object.rows; i++ ) { 
        if( matches[i].distance < 12 * min_dist ) { 
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
    
    coordArray[0] = static_cast<int>(scene_corners[0].x);
    coordArray[1] = static_cast<int>(scene_corners[0].y);
    coordArray[2] = static_cast<int>(scene_corners[1].x);
    coordArray[3] = static_cast<int>(scene_corners[1].y);
    coordArray[4] = static_cast<int>(scene_corners[2].x);
    coordArray[5] = static_cast<int>(scene_corners[2].y);
    coordArray[6] = static_cast<int>(scene_corners[3].x);
    coordArray[7] = static_cast<int>(scene_corners[3].y);
    
    return coordArray;
}