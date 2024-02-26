#include "Player.h"
        Player::Player(int initialX, int initialY, std::string wantedAscii, char wantedColour){
            position.SetNewCoordinates(initialX, initialY);
            displayAttributes.Ascii(wantedAscii);
            displayAttributes.Colour(wantedColour);
        }

        /**
         * @brief
         * # PlacedABomb
         * @brief
         * Tells you if the player has pressed a button to
         * place a bomb. This is only real if the player's
         * counter to place bomb is available.
         * @return true:
         * The player NEEDS to place a bomb next frame
         * @return false:
         * The player SHOULDN'T place a bomb on the next frame.
         */
        bool Player::PlacedABomb(){
            
        }

        /**
         * @brief
         * # Health
         * @brief
         * Tells you how much health that player has.
         * The value ranges from 0 to 100 and defaults
         * at 100. You can use @ref GiveDamage to
         * remove health from the player as well as
         * @ref GiveHealth to give health back to a
         * player.
         * @return int 
         */
        int Health();

        /**
         * @brief 
         * # GiveHealth
         * @brief 
         * Gives a certain amount of health to the player.
         * Certain powerups could give the player more
         * health. However, the starting maximum health
         * that a player can have is 100. Any value above
         * that number won't add shit.
         * @attention
         * This gives X more health to the player. This
         * does NOT set the player health to that number.
         * @param healthPoint
         * How much health should the player get?
         * @return true:
         * Successfully gave the player health
         * @return false:
         * Failed to give the player health. Already at
         * max capacity or whatever.
         */
        bool GiveHealth(int healthPoint);

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
        bool GiveDamage(int damagePoints);

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
        PowerUp* GetActivatedPowerUp();

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
