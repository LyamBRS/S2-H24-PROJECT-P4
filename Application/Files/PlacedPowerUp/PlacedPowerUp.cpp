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
   if (Timetilldespawn->TimeLeft()==0)
    {    
        shoulbedeleted=1;
        return shoulbedeleted;
    }

   if (Timetilldespawn->TimeLeft()!=0)
    {
        shoulbedeleted=0;
        return shoulbedeleted;
    }
}

bool PlacedPowerUp::ShouldBeDeleted()
{
   return shoulbedeleted
}