/**
 * @file Ray.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// - INCLUDES - //
#include "Ray.h"

// - METHODS - //
Ray::Ray(int initialX, int initialY, int endLength, float newAssociatedAngle)
{
    bombCenter.X(initialX);
    bombCenter.Y(initialY);
    end.X(initialX);
    end.Y(initialY);
    length = 0;
    maxLength = endLength;
    associatedAngle = newAssociatedAngle;
}

/**
 * @brief 
 * Increases the lenght of the ray.
 * If the max length set is reached, it will not increase its
 * length. You can set wether a wall was reached with
 * @ref SetAsEnded
 * @return true 
 * @return false 
 */
bool Ray::Update()
{
    if(!canContinueExpanding) return false;
    if(length >= maxLength)
    {
        SetAsEnded();
        return false;
    }

    length = length + 1;
    end = GetSpecificPosition(length);
    return true;
}

/**
 * @brief
 * Returns the coordinate based on a position along
 * the ray. length 0 = start.
 * Positions will be set as -1,-1 if the specified
 * length is not valid.
 * @param atThisLength 
 * @return Positions 
 */
Positions Ray::GetSpecificPosition(int atThisLength)
{
    //if(atThisLength > maxLength) return GetEndPosition();
    if(atThisLength < 0) return GetSpecificPosition(0);

    float x = (cosf(associatedAngle) * atThisLength) + (float(bombCenter.X()));
    float y = (sinf(associatedAngle) * atThisLength) + (float(bombCenter.Y()));

    if(fmod(x,1) > 0.5f) {x = ceilf(x);} else {x = floorf(x);}
    if(fmod(y,1) > 0.5f) {y = ceilf(y);} else {y = floorf(y);}

    return Positions((int(x)), (int(y)));
}

/**
 * @brief Get the End Position object
 * Returns the coordinate at the very end
 * of the ray. Used once the bomb finished
 * exploding so that we can figure out if
 * boxes need to be destroyed.
 * @return Positions 
 */
Positions Ray::GetEndPosition()
{
    return end;
}

/**
 * @brief Get the Length of the ray.
 * @return int 
 */
int Ray::GetLength()
{
    return length;
}

/**
 * @brief 
 * Says wether this ray can continue expanding or not.
 * @return true 
 * @return false 
 */
bool Ray::HasEnded()
{
    return !canContinueExpanding;
}

/**
 * @brief
 * Tells the ray that it has finished expanding.
 * @return true 
 * @return false 
 */
bool Ray::SetAsEnded()
{
    if(canContinueExpanding)
    {
        length = length - 1;
        if(length < 0) length = 0;
        canContinueExpanding = false;
        return true;
    }
    return false;
}