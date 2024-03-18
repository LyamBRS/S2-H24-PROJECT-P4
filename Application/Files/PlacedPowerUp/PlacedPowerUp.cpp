#include "PlacedPowerUp.h"
#include <Arduino.h>
#include "SimpleTimer.h"

PlacedPowerUp::PlacedPowerUp(int initialX, int initialY, int type) 
{
    this->position.SetNewCoordinates(initialX,initialY);
    
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
    case PowerUpID::powerUpFName:
        type=PowerUpID::powerUpFName;
        break;
    case PowerUpID::powerUpGName:
        type=PowerUpID::powerUpGName;
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
   return shoulbedeleted;
}