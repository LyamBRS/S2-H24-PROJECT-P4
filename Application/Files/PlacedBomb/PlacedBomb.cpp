#include "PlacedBomb.h"

PlacedBomb::PlacedBomb(int x, int y, int explosiveForce, int fuseLength){
    timeTillBoom.SetDuration(fuseLength);
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
bool PlacedBomb::Update(){ //wtf stay that size for a couple more update
    if (timeTillBoom.TimeLeft() == 0) { 
        isExploding = true;
    }
    if (isExploding && (currentExplosionRadius < explosivePower)) {
        currentExplosionRadius++;
    }
    isExploded = currentExplosionRadius >= explosivePower;
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
    return isExploded;
}

// Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
Movements* PlacedBomb::GetVelocity()
{
    return &movement;
}

Positions* PlacedBomb::GetCurrentCoordinates()
{
    return &position;
}

Positions* PlacedBomb::GetOldCoordinates()
{
    return &OldPosition;
}