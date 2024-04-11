/**
 * @file Player.cpp
 * @author
 * - YOUR NAME
 * @author
 * - YOUR NAME
 * @brief 
 * THINGS CHANGED:
 * 
 *  -   Removed 2 tabs worth of indentations. Dont put your methods in the middle of the document. I understand if you think it can take a bit, if you dont know how to mass indent, i'll gladly show you how to do it in 3 seconds :)
 *  -   PlacedABomb is supposed to already tell you if the player successfully should be placing a bomb. (read header definition) You're checking the button inside of the function. The goal of the function was to tell if the player did place a bomb. So just return wantsToPlaceBomb. 
 *  -   Health method was good.
 *  -   GiveHealth method was good.
 *  -   GiveDamage method was good.
 *  -   You didnt do UpdateFromController. You were supposed to use the Controller object, check for buttons, update movements if buttons were pressed, place a bomb is button was pressed and counter good, as well as set these button values in the Controller to false to avoid double detection.
 *  -   You are not returning anything in GetActivatedPowerUp. Functions should always return something when specified to avoid errors. (nullptr works here because powerups are not done) :P
 *  -   RemoveSelectedPowerUp shouldve just returned false. You cant not open a function and keep the ; at the end. Compilers dont like that
 *  -   Changed the code to reference a Controller rather than UpdateFromController. (thats on me, sorry)
 * @version 0.1
 * @date 2024-03-12
 * @copyright Copyright (c) 2024
 */


// - INCLUDES - //
#include "Player.h"

// - PRORGAM - //
Player::Player(int initialX, int initialY, std::string wantedAscii, int wantedColour) : BaseObject()
{
    position.SetNewCoordinates(initialX, initialY);
    OldPosition.SetNewCoordinates(initialX, initialY);
    movement.SetDeltas(0, 0);
    displayAttributes.Ascii(wantedAscii);
    displayAttributes.Colour(wantedColour);
}

bool Player::PlacedABomb()
{
    wantsToPlaceBomb = false;
    bombPlacement.Reset();
    return true;
}

bool Player::WantsToPlaceABomb()
{
    return wantsToPlaceBomb;
}

int Player::Health()
{
    return health;
}

bool Player::GiveHealth(int healthPoint){
    if(health == 100){
        return false;
    }
    health = health + healthPoint;
    if(health>100){
        health = 100;
    }
    return true;
}

/**
 * @brief
 * # GiveDamage
 * @brief
 * Used to remove health from a player. The player
 * will then enter an invulnerability phase where
 * they will NOT loose health. 
 * @param damagePoints
 * How much health should be taken away from
 * the player?
 * @return true
 * Successfully took that amount out of their health. 
 * @return false:
 * The player cant take damages at the moment.
 */
bool Player::GiveDamage(int damagePoints){
    if(invulnurability.TimeLeft() == 0)
    {
        if(health == 0){
            return false;
        }
        health = health - damagePoints;
        if(health<0){
            isAlive = false;
            health = 0;
        }
        return true;     
    }
    return false;       
}

/**
 * @brief
 * # UpdateFromController
 * @brief
 * takes a specified controller and applies its
 * various inputs into actions that the player
 * can do. Such as update its movements, place
 * a bomb, change the selected item, use the
 * selected item etc.
 * @attention
 * ## THIS DON'T CHANGE PLAYER'S POSITIONS. aight?
 * @return true:
 * Successfully updated the player's attributes
 * based on the referenced controller. 
 * @return false:
 * Failed to update the player's attributes.
 */
bool Player::UpdateFromController()
{
    static bool wasPressing = false;

    // Check if connected, if there is no controllers... we cant really control a player can we.
    if(!controllerRef->isConnected)
    {
        movement.SetDeltas(0,0);
        wantsToPlaceBomb = false;
        return false;
    }

    // Check movements
    movement.SetDeltas(0, 0);
    int wantedDeltaX = 0;
    int wantedDeltaY = 0;

    wantedDeltaX = wantedDeltaY;

    if (PLAYER_LOCAL_X_AXIS < 50 - PLAYER_CONTROLLER_THRESHOLD) movement.DeltaX(1);
    if (PLAYER_LOCAL_X_AXIS > 50 + PLAYER_CONTROLLER_THRESHOLD) movement.DeltaX(-1);

    if (PLAYER_LOCAL_Y_AXIS < 50 - PLAYER_CONTROLLER_THRESHOLD) movement.DeltaY(1);
    if (PLAYER_LOCAL_Y_AXIS > 50 + PLAYER_CONTROLLER_THRESHOLD) movement.DeltaY(-1);

    // Bomb placement handling
    if(bombPlacement.TimeLeftNoReset() == 0)
    {
        if(PLAYER_LOCAL_SELECT)
        {
            wantsToPlaceBomb = true;
            bombPlacement.Reset();
        }
    }

    // Inventory UI handling
    if(inventoryUIFrames.TimeLeftNoReset() == 0)
    {
        if(PLAYER_LOCAL_INV_RIGHT)
        {
            if(inventory.SelectNext()) 
            {
                inventoryUIFrames.Reset();
                inventoryRequiresRedraw = true;
                inventorySelectionChanged = true;
            }
        }

        if(PLAYER_LOCAL_INV_LEFT)
        {
            if(inventory.SelectPrevious()) 
            {
                inventoryUIFrames.Reset();
                inventoryRequiresRedraw = true;
                inventorySelectionChanged = true;
            }
        }

        if(PLAYER_LOCAL_USE_PWR)
        {
            if(inventory.SelectedIsUsable())
            {
                wantsToUseSelectedItem = true;
                wantsToRemoveSelectedItem = false;
                inventoryRequiresRedraw = true;
                inventoryUIFrames.Reset();
            }
        }

        if(PLAYER_LOCAL_DISCARD_PWR)
        {
            wantsToUseSelectedItem = false;
            wantsToRemoveSelectedItem = true;
            inventoryRequiresRedraw = true;
            inventoryUIFrames.Reset();
        }
    }

    return true;
}

/**
 * @brief 
 * Tells if that specific player's controller is currently
 * connected or not.
 * @return true:
 * Is connected
 * @return false:
 * Is not connected 
 */
bool Player::IsConnected()
{
    return controllerRef->isConnected;
}

bool Player::LinkController(Controller* newControllerReference)
{
    controllerRef = newControllerReference;
    return true;
}

bool Player::UnlinkController()
{
    Controller* fuckThisShit = new Controller();
    controllerRef = fuckThisShit;
    return true;
}

Controller* Player::GetController()
{
    return controllerRef;
}

// Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
Movements* Player::GetVelocity()
{
    return &movement;
}

// Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
Positions* Player::GetCurrentCoordinates()
{
    return &position;
}

// Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
Positions* Player::GetOldCoordinates()
{
    return &OldPosition;
}

/**
 * @brief
 * # NeedsToBeDeleted
 * @brief
 * Tells the game that the player should no longer be drawn 
 * on the map. 
 * @return true 
 * @return false 
 */
bool Player::NeedsToBeDeleted()
{
    return (isAlive && Health()==0 && isDead==false);
}

/**
 * @brief
 * # NeedsToBeDeleted
 * @brief
 * Tells the game that the player is no longer be drawn 
 * on the map. He dead as hell
 * @return true 
 * @return false 
 */
bool Player::SetPlayerAsDeleted()
{
    isDead = true;
    health = 0;
    return true;
}

PlacedBomb Player::GetABomb(Map* mapReference)
{
    TileTypes smokeToUse = TileTypes::BOMB; // That way the problem is immediately seen.
    switch(bombDamage)
    {
        case(1): smokeToUse=TileTypes::SMOKE;  break;
        case(2): smokeToUse=TileTypes::SMOKE1; break;
        case(3): smokeToUse=TileTypes::SMOKE2; break;
        case(4): smokeToUse=TileTypes::SMOKE3; break;
        case(5): smokeToUse=TileTypes::SMOKE4; break;
        case(6): smokeToUse=TileTypes::SMOKE5; break;
    }

    return PlacedBomb(
        position.X(),
        position.Y(),
        bombRadius,
        PLAYER_DEFAULT_BOMB_FUSE,
        bombDamage,
        mapReference,
        true,
        smokeToUse,
        false,
        true
    );
}

/**
 * @brief 
 * Simply says if we need to redraw the player's
 * inventory.
 * @return true 
 * @return false 
 */
bool Player::NeedToRedrawInventory()
{
    return inventoryRequiresRedraw;
}

bool Player::InventoryRedrawn()
{
    inventoryRequiresRedraw = false;
    return true;
}

/**
 * @brief 
 * The player wants to get rid of their selected powerup.
 * This means re-drawing their inventories.
 * @return true 
 * @return false 
 */
bool Player::WantsToDiscardSelected()
{
    return wantsToRemoveSelectedItem;
}

/**
 * @brief 
 * The player wants to use the selected powerup. This
 * means re-drawing their inventories.
 * @return true 
 * @return false 
 */
bool Player::WantsToUseSelected()
{
    return wantsToUseSelectedItem;
}

/**
 * @brief
 * # GetActivatedPowerUp
 * @brief
 * Returns a reference to the @ref PowerUp that the
 * player has currently selected AND wants to use.
 * This is used so that the powerup can be applied
 * in the game's space and later removed from their
 * inventory if needs be.
 * @warning
 * If the player DOES NOT want to use that powerup,
 * @ref nullptr is returned. BE CAREFUL.
 * @return PowerUp* 
 */
PowerUp* Player::GetActivatedPowerUp()
{
    return inventory.GetSelected();
}

bool Player::PickUpPowerUp(PowerUp pickedUp)
{
    if(inventory.IsFull()) return false;
    inventoryRequiresRedraw = true;
    return inventory.Add(pickedUp);
}

/**
 * @brief
 * # RemoveSelectedPowerUp
 * @brief
 * Removes the currently selected @ref PowerUp from
 * the player's inventory. They will no longer be
 * able to see that @ref PowerUp nor use it.
 * @return true:
 * Successfully removed the power up.
 * @return false:
 * Failed to remove the power up.
 */
bool Player::RemoveSelectedPowerUp()
{
    if(!inventory.SelectedIsUsable()) return false;
    inventoryRequiresRedraw = true;
    wantsToRemoveSelectedItem = false;
    inventory.DiscardSelected();
    return true;
}

/**
 * @brief 
 * Makes the user use their current selected Power ups.
 * @return true 
 * @return false 
 */
bool Player::UseSelected()
{
    if(!inventory.SelectedIsUsable()) return false;
    inventoryRequiresRedraw = true;
    wantsToUseSelectedItem = false;
    inventory.UseSelected();
    return true;
}

bool Player::SetBombRadius(int newRadius)
{
    bombRadius = newRadius;
    return true;
}
int Player::GetBombRadius()
{
    return bombRadius;
}

bool Player::SetBombDamage(int newDamage)
{
    bombDamage = newDamage;
    return true;
}
int Player::GetBombDamage()
{
    return bombDamage;
}

Inventory* Player::GetInventory()
{
    return &inventory;
}

bool Player::HasSelectedNewItemSinceLastTime()
{
    if (inventorySelectionChanged)
    {
        inventorySelectionChanged = false;
        return true;
    }
    return false;
}



// - FUNCTIONS - //
bool AffectPlayer_HealthBonus(Player* player)
{
    player->GiveHealth(PLAYER_HEALTH_BONUS);
    return true;
}

bool AffectPlayer_SpeedBonus(Player* player)
{
    int current = player->movementFrameDelay.GetDuration();
    current -= PLAYER_BONUS_SPEED;
    if(current < PLAYER_MIN_SPEED_INTERVALS) current = PLAYER_MIN_SPEED_INTERVALS;
    player->movementFrameDelay.SetDuration(current);
    return true;
}

bool AffectPlayer_BombRadiusBonus(Player* player)
{
    int current = player->GetBombRadius();
    current += PLAYER_BOMB_RADIUS_BONUS;
    if(current > PLAYER_MAX_BOMB_RADIUS) current = PLAYER_MAX_BOMB_RADIUS;
    player->SetBombRadius(current);
    return true;
}

bool AffectPlayer_BombDamageBonus(Player* player)
{
    int current = player->GetBombDamage();
    current += PLAYER_BOMB_DAMAGE_BONUS;
    if(current > PLAYER_MAX_BOMB_DMG) current = PLAYER_MAX_BOMB_DMG;
    player->SetBombDamage(current);
    return true;
}

bool AffectPlayer_BombPlacementSpeed(Player* player)
{
    int current = player->bombPlacement.GetDuration();
    current -= PLAYER_BOMB_PLACEMENT_BONUS;
    if(current < PLAYER_MIN_BOMB_INTERVALS) current = PLAYER_MIN_BOMB_INTERVALS;
    player->bombPlacement.SetDuration(current);
    return true;
}