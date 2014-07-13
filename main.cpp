#include "flighttracker.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[]) {
    
    int screenX = 1000;
    int screenY = 600;

    QApplication app(argc, argv);
    
    FlightTracker flightTracker;
    
    QDesktopWidget widget;
    
    QRect screenSize = widget.availableGeometry(widget.primaryScreen());
    
    flightTracker.setWindowTitle("Flight tracker");
    
    flightTracker.setGeometry((screenSize.width() / 2) - (screenX / 2), (screenSize.height() / 2) - (screenY / 2), screenX, screenY);
    flightTracker.show();

    return app.exec();
}
