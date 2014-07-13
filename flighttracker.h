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
    void refreshRect(QImage *dest);
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
    
    QTimer *camTimer;
    
};

#endif	/* FLIGHTTRACKER_H */

