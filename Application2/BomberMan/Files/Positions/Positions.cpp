#include "Positions.h"

Positions::Positions(int initialX, int initialY){
    x=initialX;
    y=initialY;
}

bool Positions::SetNewCoordinates(int newX, int newY){
    x=newX;
    y=newY;
    return true;
}

int Positions::X(){
    return x;
}

int Positions::X(int newX){
    x = newX;
    return 1;
}

int Positions::Y(){
    return y;
}

int Positions::Y(int newY){
    y = newY;
    return 1;
}

bool Positions::operator==(Positions comparator)
{
    if((X()==comparator.X()) && (Y()==comparator.Y())) return true;
    return false;
}