#include "PlacedPowerUp.h"
#include <Arduino.h>

PlacedPowerUp::PlacedPowerUp(int initialX, int initialY, int type)
{
    this->setPosition(initialX, initialY);
    this->type = type;
}

int PlacedPowerUp::GetType()
{
    return type;
}

bool PlacedPowerUp::Update()
{
    this->timeTillDespawn -= 1;
    return True;
}

bool PlacedPowerUp::ShouldBeDeleted()
{
    if (this->timeTillDespawn <= 0) {
        return true;
    } else {
        return false;
    }
}
