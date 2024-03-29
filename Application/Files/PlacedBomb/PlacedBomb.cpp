#include "PlacedBomb.h"

float GetRaycastAngleIncrement(int bombFinalRadius)
{
    return 6.28f / (2*bombFinalRadius);
}

int GetAngleGenericDirection(float angle)
{
    if((angle > (6.28f-ANGLE_THRESHOLD)) || (angle < (ANGLE_THRESHOLD)))           return 0; 
    if((angle > (ANGLE_T-ANGLE_THRESHOLD)) && (angle < (ANGLE_T+ANGLE_THRESHOLD))) return 2;
    if((angle > (ANGLE_B-ANGLE_THRESHOLD)) && (angle < (ANGLE_B+ANGLE_THRESHOLD))) return 6;
    if((angle > (ANGLE_L-ANGLE_THRESHOLD)) && (angle < (ANGLE_L+ANGLE_THRESHOLD))) return 4;

    if((angle> (ANGLE_BR-ANGLE_THRESHOLD)) && (angle < (ANGLE_BR+ANGLE_THRESHOLD))) return 7;
    if((angle> (ANGLE_BL-ANGLE_THRESHOLD)) && (angle < (ANGLE_BL+ANGLE_THRESHOLD))) return 5;
    if((angle> (ANGLE_TR-ANGLE_THRESHOLD)) && (angle < (ANGLE_TR+ANGLE_THRESHOLD))) return 1;
    if((angle> (ANGLE_TL-ANGLE_THRESHOLD)) && (angle < (ANGLE_TL+ANGLE_THRESHOLD))) return 3;
    return -1;
}




PlacedBomb::PlacedBomb(int x, int y, int explosiveForce, int fuseLength, int damagePerTick, Map* newMapReference, bool clearOnceFinished, TileTypes usedTile, bool stopOnPlayer, bool canDestroyBoxes){
    timeTillBoom.SetDuration(fuseLength);
    explosivePower = explosiveForce;
    position.SetNewCoordinates(x,y);
    mapReference = newMapReference;
    damage = damagePerTick;
    wantedTile = usedTile;
    clearAtEnd = clearOnceFinished;
    canDestroy = canDestroyBoxes;
    stopOnPlayers = stopOnPlayer;

    Positions right         = Positions(x+1,y);
    Positions topRight      = Positions(x+1,y-1);
    Positions top           = Positions(x,y-1);
    Positions topLeft       = Positions(x-1,y-1);
    Positions Left          = Positions(x-1,y);
    Positions bottomLeft    = Positions(x-1,y+1);
    Positions bottom        = Positions(x,y+1);
    Positions bottomRight   = Positions(x+1,y+1);

    if(mapReference->GetTileDataAtPosition(right)       != TileTypes::PERMAWALL) canGo_R=true;
    if(mapReference->GetTileDataAtPosition(topRight)    != TileTypes::PERMAWALL) canGo_TR=true;
    if(mapReference->GetTileDataAtPosition(top)         != TileTypes::PERMAWALL) canGo_U=true;
    if(mapReference->GetTileDataAtPosition(topLeft)     != TileTypes::PERMAWALL) canGo_TL=true;
    if(mapReference->GetTileDataAtPosition(Left)        != TileTypes::PERMAWALL) canGo_L=true;
    if(mapReference->GetTileDataAtPosition(bottomLeft)  != TileTypes::PERMAWALL) canGo_BL=true;
    if(mapReference->GetTileDataAtPosition(bottom)      != TileTypes::PERMAWALL) canGo_D=true;
    if(mapReference->GetTileDataAtPosition(bottomRight) != TileTypes::PERMAWALL) canGo_BR=true;

    if(canGo_BL && !canGo_L) canGo_BL = false;
    if(canGo_TL && !canGo_L) canGo_TL = false;
    if(canGo_BR && !canGo_R) canGo_BR = false;
    if(canGo_TR && !canGo_R) canGo_TR = false;

    if(canGo_TL && !canGo_U) canGo_TL = false;
    if(canGo_TR && !canGo_U) canGo_TR = false;
    if(canGo_BR && !canGo_D) canGo_BR = false;
    if(canGo_BL && !canGo_D) canGo_BL = false;

    //SetTerminalCursorPosition(0,0);
    //std::cout << "R: " << canGo_R << " TR: " << canGo_TR << " T: " << canGo_U << " TL: " << canGo_TL << " L: " << canGo_L << " BL: " << canGo_BL << " B: " << canGo_D << " BR: " << canGo_BR << std::endl;

    float initialAngle = GetRaycastAngleIncrement(explosiveForce);
    for(int i=0; i < 2*explosiveForce; i++)
    {
        rays.push_back(Ray(x, y, explosiveForce, initialAngle));

        bool cantGo = true;

        // Test to see if we need to terminate that raycast before it even started based on walls directly next to the bomb.
        if(!canGo_R &&  ((initialAngle > (6.28f-ANGLE_THRESHOLD)) || (initialAngle < (ANGLE_THRESHOLD))))           {rays[i].SetAsEnded(); cantGo=false;}
        if(!canGo_U &&  ((initialAngle > (ANGLE_T-ANGLE_THRESHOLD)) && (initialAngle < (ANGLE_T+ANGLE_THRESHOLD)))) {rays[i].SetAsEnded(); cantGo=false;}
        if(!canGo_D &&  ((initialAngle > (ANGLE_B-ANGLE_THRESHOLD)) && (initialAngle < (ANGLE_B+ANGLE_THRESHOLD)))) {rays[i].SetAsEnded(); cantGo=false;}
        if(!canGo_L &&  ((initialAngle > (ANGLE_L-ANGLE_THRESHOLD)) && (initialAngle < (ANGLE_L+ANGLE_THRESHOLD)))) {rays[i].SetAsEnded(); cantGo=false;}

        if(!canGo_BR &&  ((initialAngle > (ANGLE_BR-ANGLE_THRESHOLD)) && (initialAngle < (ANGLE_BR+ANGLE_THRESHOLD)))) {rays[i].SetAsEnded(); cantGo=false;}
        if(!canGo_BL &&  ((initialAngle > (ANGLE_BL-ANGLE_THRESHOLD)) && (initialAngle < (ANGLE_BL+ANGLE_THRESHOLD)))) {rays[i].SetAsEnded(); cantGo=false;}
        if(!canGo_TR &&  ((initialAngle > (ANGLE_TR-ANGLE_THRESHOLD)) && (initialAngle < (ANGLE_TR+ANGLE_THRESHOLD)))) {rays[i].SetAsEnded(); cantGo=false;}
        if(!canGo_TL &&  ((initialAngle > (ANGLE_TL-ANGLE_THRESHOLD)) && (initialAngle < (ANGLE_TL+ANGLE_THRESHOLD)))) {rays[i].SetAsEnded(); cantGo=false;}

        initialAngle = initialAngle + GetRaycastAngleIncrement(explosiveForce);
    }
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
        UpdateRays();
        CheckAllRaysForCollisions();
    }

    if(AllRaysFinished() || (currentExplosionRadius >= explosivePower))
    {
        isExploded = true;
        currentExplosionRadius = explosivePower;
    }
    
    if(isExploded && !hasFinishedFrames)
    {
        endFrameCounter--;
        hasFinishedFrames = endFrameCounter<0;
    }
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
    return hasFinishedFrames;
}

bool PlacedBomb::IsExploding()
{
    return isExploding;
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

bool PlacedBomb::UpdateRays()
{
    for(int i=0; i<rays.size(); i++)
    {
        rays[i].Update();
    }
    return true;
}

bool PlacedBomb::CheckAllRaysForCollisions()
{
    for(int i=0; i<rays.size(); i++)
    {
        if(rays[i].HasEnded()) continue;

        Positions rayEnd = rays[i].GetEndPosition();
        TileTypes tileThere = mapReference->GetTileDataAtPosition(rayEnd);

        if(!TileIsWalkable(tileThere) || (checkIfTileIsPlayer(tileThere) && stopOnPlayers))
        {
            rays[i].SetAsEnded();
            continue;
        }

        // Get associated diagonals to avoid exploding through diagonal gaps
        float angle = rays[i].Angle();
        int genericDirection = GetAngleGenericDirection(angle);

        Positions posA = Positions(0,0);
        Positions posB = Positions(0,0);
        switch(genericDirection)
        {
            case(1):
                posA = Positions(rayEnd.X()+1, rayEnd.Y());
                posB = Positions(rayEnd.X(), rayEnd.Y()-1);
                break;
            
            case(3):
                posA = Positions(rayEnd.X()-1, rayEnd.Y());
                posB = Positions(rayEnd.X(), rayEnd.Y()-1);
                break;

            case(5):
                posA = Positions(rayEnd.X()-1, rayEnd.Y());
                posB = Positions(rayEnd.X(), rayEnd.Y()+1);
                break;

            case(7):
                posA = Positions(rayEnd.X()+1, rayEnd.Y());
                posB = Positions(rayEnd.X(), rayEnd.Y()+1);
                break;

            default:
                continue;
                break;
        }

        TileTypes tileA = mapReference->GetTileDataAtPosition(posA);
        TileTypes tileB = mapReference->GetTileDataAtPosition(posB);

        bool tileAIsValid = !TileIsWalkable(tileA) || (checkIfTileIsPlayer(tileA) && stopOnPlayers);
        bool tileBIsValid = !TileIsWalkable(tileB) || (checkIfTileIsPlayer(tileB) && stopOnPlayers);

        if(tileAIsValid && tileBIsValid)
        {
            rays[i].SetAsEnded();
            continue;
        }
    }
    return true;
}

bool PlacedBomb::AllRaysFinished()
{
    bool result = true;
    for(int i=0; i<rays.size(); i++)
    {
    // SetTerminalCursorPosition(60,i);
        if(!rays[i].HasEnded())
        {
            // std::cout << "i: " << i << ": U";
            result = false;
        }
        else
        {
            // std::cout << "i: " << i << ": F";
        }
    }
    return result;
}

bool PlacedBomb::IsInsideExplosion(int x, int y)
{
    // Ill just check if the player's wanted tile is a smoke tile for damage detection. Its a lot less ressource intensive.
    Positions verified = Positions(x,y);
    for(int r = 0; r<rays.size(); r++)
    {
        for(int l=0; l<=rays[r].GetLength(); l++)
        {
            Positions coordinate = rays[r].GetSpecificPosition(l);
            if(verified == coordinate) return true;
        }
    }
    return false;
}

bool PlacedBomb::Draw()
{
    for(int i=0; i<rays.size(); i++)
    {
        for(int l=0; l<=rays[i].GetLength(); l++)
        {
            Positions coordinateInRay = rays[i].GetSpecificPosition(l);
            mapReference->SetTileDataAtPosition(
                coordinateInRay.X(),
                coordinateInRay.Y(),
                wantedTile
            );
        }
    }
    return true;
}

bool PlacedBomb::Clear()
{
    if(!clearAtEnd) return false;
    for(int i=0; i<rays.size(); i++)
    {
        for(int l=0; l<=rays[i].GetLength(); l++)
        {
            Positions coordinateInRay = rays[i].GetSpecificPosition(l);
            TileTypes tileAtThatCoordinate = mapReference->GetTileDataAtPosition(coordinateInRay);

            if(tileAtThatCoordinate == wantedTile)
            {
                mapReference->SetTileDataAtPosition(
                    coordinateInRay.X(),
                    coordinateInRay.Y(),
                    TileTypes::EMPTY
                );
            }
        }
    }
    return true;
}

bool PlacedBomb::CanDestroy()
{
    return canDestroy;
}

int PlacedBomb::GetDamagePoints()
{
    if(!isExploding) return 0;
    return damage;
}