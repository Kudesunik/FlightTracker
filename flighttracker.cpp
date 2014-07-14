#include <qt4/QtCore/qglobal.h>
#include <qt4/QtGui/qlabel.h>
#include <sstream>
#include <opencv2/core/core.hpp>

#include "flighttracker.h"
#include "detector.h"

Detector *det = new Detector();

FlightTracker::FlightTracker() {
    setGUIElements();
    camTimer = new QTimer(this);
    connect(camTimer, SIGNAL(timeout()), this, SLOT(refreshPic()));
    camTimer -> start(1000);
    timeFlag = FALSE;
    start = time(0);
    frameFlag = 2;
}

void FlightTracker::setGUIElements() {
    
    camLabel = new QLabel("Camera 1");
    dXLabel = new QLabel("dX");
    dYLabel = new QLabel("dY");
    movXLabel = new QLabel("moving X");
    movYLabel = new QLabel("moving Y");
    
    i_label = new QLabel("Start", this);
    pixmap = new QPixmap(800, 600);
    pixmap -> load(QString::fromUtf8("dummy.png"));
    i_label -> setPixmap(*pixmap);

    dX = new QLineEdit();
    dX -> setReadOnly(TRUE);
    dX -> setText("Unknown");
    
    dY = new QLineEdit();
    dY -> setReadOnly(TRUE);
    dY -> setText("Unknown");
    
    movX = new QLineEdit();
    movX -> setReadOnly(TRUE);
    movX -> setText("Unknown");
    
    movY = new QLineEdit();
    movY -> setReadOnly(TRUE);
    movY -> setText("Unknown");
    
    gridLayout = new QGridLayout(this);
    formLayout = new QFormLayout(this);
    
    gridLayout -> addLayout(formLayout, 1, 2);
    
    camLabel -> setAlignment(Qt::AlignCenter);
    gridLayout -> addWidget(camLabel, 0, 1);
    gridLayout -> addWidget(i_label, 1, 1);
    gridLayout -> setAlignment(Qt::AlignLeft);
    
    formLayout -> addRow(dXLabel);
    formLayout -> addRow(dX);
    formLayout -> addRow(dYLabel);
    formLayout -> addRow(dY);
    formLayout -> addRow(movXLabel);
    formLayout -> addRow(movX);
    formLayout -> addRow(movYLabel);
    formLayout -> addRow(movY);
}

void FlightTracker::refreshPic() {
    
    double fps = det -> cap -> get(CV_CAP_PROP_FPS);
    camTimer -> setInterval(fps);
    
    Mat frame;
    if (det -> cap -> isOpened()) {
        det -> cap -> read(frame);
        
        QImage dest = cvMatToQImage(frame);
        
        if (timeFlag) {
                refreshRect(&dest, &frame);
        }
        else if (difftime(time(0), start) > 10) {
                timeFlag = TRUE;
        }
        
        QPixmap img = QPixmap::fromImage(dest);
        i_label -> setPixmap(img);
        this -> resize((det -> dWidth) + 200, (det -> dHeight));
    }
    else {
        i_label -> setPixmap(*pixmap);
        this -> resize(800, 600);
        det -> refreshCap();
    }
}

QImage FlightTracker::cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
            return image;
         }
 
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
            return image.rgbSwapped();
         }
 
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;
 
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back(qRgb( i, i, i ));
            }
 
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
 
            image.setColorTable( sColorTable );
            return image;
         }
 
         default:
            break;
      }
 
      return QImage();
   }

void FlightTracker::refreshRect(QImage *dest, Mat *frame) {
    
    int* coordsArr = NULL;
    
    painter = new QPainter(dest);
    redPen = new QPen((QColor(255,0,0)),1);
    redPen -> setWidth(2);
    painter -> setPen(*redPen);
    
    if (frameFlag >= 0) {
        coordsArr = (det -> detectObject(frame));
        frameFlag = 0;
    }
    else {
        frameFlag++;
    }
    
    painter -> drawLine(coordsArr[0], coordsArr[1], coordsArr[2], coordsArr[3]);
    painter -> drawLine(coordsArr[2], coordsArr[3], coordsArr[4], coordsArr[5]);
    painter -> drawLine(coordsArr[4], coordsArr[5], coordsArr[6], coordsArr[7]);
    painter -> drawLine(coordsArr[6], coordsArr[7], coordsArr[0], coordsArr[1]);
    
    int centerArr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    centerArr[0] = abs(coordsArr[4] - coordsArr[0]) / 2;
    centerArr[1] = abs(coordsArr[5] - coordsArr[1]) / 2;
    
    //painter -> drawLine(coordsArr[0], coordsArr[1], coordsArr[0] + centerArr[0], coordsArr[1] + centerArr[1]);
    
    int minValX = coordsArr[0];
    int i = 0;
    for (i = 2; i < 8; i += 2) {
        if (coordsArr[i] < minValX) {
            minValX = coordsArr[i];
        }
    }
    
    int minValY = coordsArr[1];
    int j = 0;
    for (int j = 1; j < 8; j += 2) {
        if (coordsArr[j] < minValY) {
            minValY = coordsArr[j];
        }
    }
    
    painter -> drawEllipse(minValX + centerArr[0] - 8, minValY + centerArr[1] - 8, 20, 20);
    
    updateMovingLogic(minValX + centerArr[0], minValX + centerArr[1]);
    
    //painter -> drawLine(minValX, minValY, minValX + centerArr[0], minValY + centerArr[1]);
    
    painter -> end();
}

void FlightTracker::refreshValues(int arr[]) {
    std::ostringstream str;
    str.str(""); str << arr[0];
    dX -> setText(str.str().c_str());
    str.str(""); str << arr[1];
    dY -> setText(str.str().c_str());
    str.str(""); str << arr[2];
    movX -> setText(str.str().c_str());
    str.str(""); str << arr[3];
    movY -> setText(str.str().c_str());
}

/**
 * int[0] = dX
 * int[1] = dY
 * int[2] = movX
 * int[3] = movY
 */
void FlightTracker::updateMovingLogic(int x, int y) {
    int finalArr[] = {0, 0, 0, 0};
    
    /* Here is moving logic code */
    
    /* End of moving logic code */
    
    if (finalArr[0] != 0 || finalArr[1] != 0 || finalArr[2] != 0 || finalArr[3] != 0) {
        refreshValues(finalArr);
    }
}

