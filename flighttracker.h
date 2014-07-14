#ifndef FLIGHTTRACKER_H
#define	FLIGHTTRACKER_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QFormLayout>
#include <QPainter>
#include <QPixmap>
#include <QPen>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace cv;
using namespace std;

class FlightTracker : public QWidget {
    
    Q_OBJECT
            
public:
    FlightTracker();
    QLineEdit *dX;
    QLineEdit *dY;
    QLineEdit *movX;
    QLineEdit *movY;
    QLabel *imageLabel;
    QLabel *i_label;
    QPixmap *pixmap;
    QPainter *painter;
        
protected:
    void setGUIElements();
            
protected slots:
    void refreshPic();
    void refreshRect(QImage *dest, Mat *frame);
    void updateMovingLogic();
    
private:
    void refreshValues(int arr[]);
    QLabel *camLabel;
    QLabel *dXLabel;
    QLabel *dYLabel;
    QLabel *movXLabel;
    QLabel *movYLabel;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QPen *redPen;
    QImage cvMatToQImage( const cv::Mat &inMat );
    QTimer *camTimer;
    time_t start;
    bool timeFlag;
    int frameFlag;
    
};

#endif	/* FLIGHTTRACKER_H */

