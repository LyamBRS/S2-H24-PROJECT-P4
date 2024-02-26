#include "Player.h"
        Player::Player(int initialX, int initialY, std::string wantedAscii, char wantedColour){
            position.SetNewCoordinates(initialX, initialY);
            displayAttributes.Ascii(wantedAscii);
            displayAttributes.Colour(wantedColour);
        }

        bool Player::PlacedABomb(){
            //UpdateFromController();
            if(leftButton == true){
                wantsToPlaceBomb = true;
            }
            return false;
        }

        int Player::Health(){
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
         * @param controller
         * Reference to the controller associated with the
         * plyer.
         * @return true:
         * Successfully updated the player's attributes
         * based on the referenced controller. 
         * @return false:
         * Failed to update the player's attributes.
         */
        bool UpdateFromController(Controller* controller);

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
        PowerUp* Player::GetActivatedPowerUp(){
            //UpdateFromController();
            if(rightButton == true){
                wantsToUseSelectedItem = true;
            }
            
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
        bool RemoveSelectedPowerUp();
