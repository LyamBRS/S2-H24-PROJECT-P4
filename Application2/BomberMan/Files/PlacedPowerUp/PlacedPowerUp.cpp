#include "PlacedPowerUp.h"

PlacedPowerUp::PlacedPowerUp(int initialX, int initialY, int newType) : BaseObject()
{
    this->position.SetNewCoordinates(initialX,initialY);
    
    type = newType;
    switch (type)
    {
    case PowerUpID::damage_increase:
        type=PowerUpID::damage_increase;
        break;
    case PowerUpID::speed_increase:
        type=PowerUpID::speed_increase;
        break;
    case PowerUpID::explosion_radius_increase:
        type=PowerUpID::explosion_radius_increase;
        break;
    case PowerUpID::health_increase:
        type=PowerUpID::health_increase;
        break;
    case PowerUpID::nb_bomb_increase:
        type=PowerUpID::nb_bomb_increase;
        break;
    case PowerUpID::powerUpHName:
        type=PowerUpID::powerUpHName;
        break;
     case PowerUpID::powerUpIName:
        type=PowerUpID::powerUpIName;
        break;
    case PowerUpID::powerUpKName:
        type=PowerUpID::powerUpKName;
        break;
    case PowerUpID::powerUpMName:
        type=PowerUpID::powerUpMName;
        break;
    case PowerUpID::powerUpNName:
        type=PowerUpID::powerUpNName;
        break;
    default:
        break;
    }
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
   return false;
}

bool PlacedPowerUp::ShouldBeDeleted()
{
   return shoulbedeleted;
}

// Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
Movements* PlacedPowerUp::GetVelocity()
{
    return &movement;
}

Positions* PlacedPowerUp::GetCurrentCoordinates()
{
    return &position;
}

Positions* PlacedPowerUp::GetOldCoordinates()
{
    return &OldPosition;
}

int PlacedPowerUp::GetType()
{
    return type;
}