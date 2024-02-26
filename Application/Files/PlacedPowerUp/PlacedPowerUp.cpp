#include "PlacedPowerUp.h"
#include <Arduino.h>
#include "SimpleTimer.h"

PlacedPowerUp::PlacedPowerUp(int initialX, int initialY, int type)
{

}

PlacedPowerUp::~PlacedPowerUp()
{

}

bool PlacedPowerUp::Update()
{
    
}

bool PlacedPowerUp::ShouldBeDeleted()
{
    
    uint64_t PowerAvailable = TimeLeft();
    if((timeTillDespawn - PowerAvailable) >= timeTillDespawn)
    {
        return true;
    }
    else
    {
        return false;
    }
}