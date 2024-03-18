#include "PowerUp.h"
#include <Arduino.h>

PowerUp::~PowerUp()
{
}

PowerUp::PowerUp(PlacedPowerUp* powerUpToPickUp)
{
    this->type = powerUpToPickUp->GetType(); // donne le type de quand le power up est place
}

// Function to get the power-up value based on type
unsigned int PowerUp::getPowerUpValue(int type) 
{
    PowerUpID powerUpID;

    switch (type) {
        case 0:
            name = "vitesse";
            break; // N'oubliez pas les break pour quitter le switch après chaque cas
        case 1:
            name = "soin";
            break;
        case 2:
            name = "grosseBombe";
            break;
        case 3:
            name = "tresGrosseBombe";
            break;
        case 4:
            name = "augmentationDegat";
            break;
        default:
            name = "Unknown";
            break;
    }

    static std::unordered_map<std::string, unsigned int> powerUpMap = {
        {"vitesse", powerUpID.vitesse},
        {"soin", powerUpID.soin},
        {"grosseBombe", powerUpID.grosseBombe},
        {"tresGrosseBombe", powerUpID.tresGrosseBombe},
        {"augmentationDegat", powerUpID.augmentationDegat},
    };

    // vérifier si le nom du power-up est "Unknown" avant de le rechercher dans la map
    if (name != "Unknown") {
        return powerUpMap[name];
    } else {
        // Gérer le cas où le nom du power-up est inconnu
        return 0; // Par exemple, retourner une valeur par défaut
    }
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
    return type:
}




//plus de dégat
//plus rapide
//la porter de l'explosion est plus grande