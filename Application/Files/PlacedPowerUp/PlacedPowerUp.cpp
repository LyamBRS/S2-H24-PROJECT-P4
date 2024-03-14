#include "PlacedPowerUp.h"
#include <Arduino.h>
#include "SimpleTimer.h"

PlacedPowerUp::PlacedPowerUp(int initialX, int initialY, int type) 
{
    this->position.SetNewCoordinates(initialX,initialY);
    this->type=type;
}

PlacedPowerUp::~PlacedPowerUp()
{

}

bool PlacedPowerUp::Update()
{
    if (ShouldBeDeleted())
    {return true;}
    else if (!ShouldBeDeleted())
    {return false;}
}

bool PlacedPowerUp::ShouldBeDeleted()
{
   if (Timetilldespawn->TimeLeft()==0)
   {return true;}
   if (Timetilldespawn->TimeLeft()!=0)
   {return false;}
}