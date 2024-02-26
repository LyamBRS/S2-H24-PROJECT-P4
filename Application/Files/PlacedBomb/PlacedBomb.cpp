#include "PlacedBomb.h"

        PlacedBomb::PlacedBomb(int x, int y, int explosiveForce, int fuseLength){
            timeTillBoom = fuseLength;
            explosivePower = explosiveForce;
            position.SetNewCoordinates(x,y);
        }

        /**
         * @brief 
         * Updates the bomb object. This allows the
         * object to update its sprite and its timers
         * The bomb will firstly count down then it
         * will explode until it reaches its maximum
         * radius after which it will stay that size
         * for a couple more updates until its done
         * animating.
         * @return true:
         * Successfully updated the placed bomb
         * @return false:
         * Failed to update the bomb. The bomb is
         * finished exploding.
         */
        bool PlacedBomb::Update(){
            if (HasFinishedExploding() == true)
            {
                return false;
            }
            currentExplosionRadius+=1;
            return true;
        }

        /**
         * @brief 
         * Tells you if the bomb has finished fully
         * exploding. You then must delete this object.
         * @return true:
         * The bomb is done doing bomb shit.
         * @return false:
         * Bomb still doing bomb shit.
         */
        bool PlacedBomb::HasFinishedExploding(){
            if(currentExplosionRadius <= explosivePower){
                return false;
            }
            currentExplosionRadius = 0;
            return true;
        }