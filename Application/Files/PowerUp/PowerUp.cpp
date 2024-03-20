#include "PowerUp.h"

PowerUp::PowerUp(int powerUpID, int amountOfUses)
{
   type = powerUpID;
   useLeft = amountOfUses;
}

// Function to get the power-up value based on type
unsigned int PowerUp::getPowerUpValue(int type) 
{
    PowerUpID powerUpID;

    switch (type) {
        case PowerUpID::speed_increase:
            name = "vitesse";
            break; // N'oubliez pas les break pour quitter le switch après chaque cas
        case PowerUpID::health_increase:
            name = "soin";
            break;
        case PowerUpID::nb_bomb_increase:
            name = "grosseBombe";
            break;
        case PowerUpID::explosion_radius_increase:
            name = "tresGrosseBombe";
            break;
        case PowerUpID::damage_increase:
            name = "augmentationDegat";
            break;
        default:
            name = "Unknown";
            break;
    }
    return 0;
}
        
std::string PowerUp::getDescription()
{
    return description;
}
        
        
void PowerUp::setDescription(std::string nom)
{
    description = nom;
}

int PowerUp::getType()
{
    return type;
}


bool PowerUp::Use()
{
    if(useLeft <= 0) return false;
    useLeft--;
    return true;
}

bool PowerUp::IsDrained()
{
    return useLeft==0;
}

int PowerUp::GetUsesLeft()
{
    return useLeft;
}

std::string GetPowerUpName(int ID)
{
    std::map<int, std::string> names = 
    {
        { PowerUpID::nil,                            "UNDEFINED"},
        { PowerUpID::damage_increase,                "DAMAGE INCREASE"},
        { PowerUpID::explosion_radius_increase,      "EXPLOSION RADIUS"},
        { PowerUpID::health_increase,                "HEALTH PACK"},
        { PowerUpID::nb_bomb_increase,               "MORE BOMBS"},
        { PowerUpID::speed_increase,                 "SPEED INCREASE"},
        { PowerUpID::bombWall,                       "BOMB OF WALLS"},
        { PowerUpID::deployableWall,                 "DEPLOYABLE WALL"},
    };
    
    return names[ID];
}

//plus de dégat
//plus rapide
//la porter de l'explosion est plus grande