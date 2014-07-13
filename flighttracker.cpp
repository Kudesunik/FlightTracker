#include <qt4/QtCore/qglobal.h>
#include <qt4/QtGui/qlabel.h>
#include <sstream>

#include "flighttracker.h"
#include "detector.h"

Detector *det = new Detector();

FlightTracker::FlightTracker() {
    setGUIElements();
    camTimer = new QTimer(this);
    connect(camTimer, SIGNAL(timeout()), this, SLOT(refreshPic()));
    camTimer -> start(2000);
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
    Mat frame;
    if (det -> cap -> isOpened()) {
        det -> cap -> read(frame);
        Mat temp;
        cvtColor(frame, temp,CV_BGR2RGB);
        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
        dest.bits();
        refreshRect(&dest);
        QPixmap img = QPixmap::fromImage(dest);
        i_label -> setPixmap(img);
        this -> resize((det -> dWidth) + 200, (det -> dHeight));
    }
    else {
        i_label -> setPixmap(*pixmap);
        this -> resize(800, 600);
        det -> refreshCap();
        if (det -> cap -> isOpened()) {
            camTimer -> setInterval(det -> cap -> get(CV_CAP_PROP_FPS));
        }
    }
    updateMovingLogic();
}

void FlightTracker::refreshRect(QImage *dest) {
    painter = new QPainter(dest);
    redPen = new QPen((QColor(255,0,0)),1);
    redPen -> setWidth(2);
    painter -> setPen(*redPen);
    int* arr = (det -> getQuadCoords());
    painter -> drawRect(arr[0], arr[1], arr[2], arr[3]);
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
void FlightTracker::updateMovingLogic() {
    int finalArr[] = {0, 0, 0, 0};
    
    /* Here is moving logic code */
    
    /* End of moving logic code */
    
    if (finalArr[0] != 0 || finalArr[1] != 0 || finalArr[2] != 0 || finalArr[3] != 0) {
        refreshValues(finalArr);
    }
}

