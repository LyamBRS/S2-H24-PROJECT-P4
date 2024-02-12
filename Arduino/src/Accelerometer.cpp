#include "Accelerometer.h"

    bool Accelerometer::SetMax(int newMaxX, int newMaxY, int newMaxZ){
        newMaxX = 1023;
        newMaxY = 1023;
        newMaxZ = 1023;
        return true;
    }

    bool Accelerometer::SetMin(int newMinX, int newMinY, int newMinZ){
        newMinX = 0;
        newMinY = 0;
        newMinZ = 0;
    }

    int Accelerometer::GetPourcentX(){
        return ((xAxis/newMaxX)*100);
    }
