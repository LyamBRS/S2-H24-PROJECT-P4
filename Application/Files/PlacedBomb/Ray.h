/**
 * @file Ray.h
 * @author LyamBRS
 * @brief
 * Used to create a ray for raycast
 * style bomb explosions.
 * Each bomb holds a vector of rays
 * which they update according to map
 * tiles.
 * @version 0.1
 * @date 2024-03-18
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "../Positions/Positions.h"
#include "math.h"

// - DEFINES - //

// - CLASS - //

class Ray
{
    float associatedAngle = 0.0f;
    bool canContinueExpanding = true;
    int length = 0;
    int maxLength = 0;
    Positions bombCenter = Positions(0,0);
    Positions end = Positions(0,0);

    public:

        Ray(int initialX, int initialY, int endLength, float newAssociatedAngle);

        /**
         * @brief 
         * Increases the lenght of the ray.
         * If the max length set is reached, it will not increase its
         * length. You can set wether a wall was reached with
         * @ref SetAsEnded
         * @return true 
         * @return false 
         */
        bool Update();

        /**
         * @brief
         * Returns the coordinate based on a position along
         * the ray. length 0 = start.
         * Positions will be set as -1,-1 if the specified
         * length is not valid.
         * @param atThisLength 
         * @return Positions 
         */
        Positions GetSpecificPosition(int atThisLength);

        /**
         * @brief Get the End Position object
         * Returns the coordinate at the very end
         * of the ray. Used once the bomb finished
         * exploding so that we can figure out if
         * boxes need to be destroyed.
         * @return Positions 
         */
        Positions GetEndPosition();

        /**
         * @brief Get the Length of the ray.
         * @return int 
         */
        int GetLength();

        /**
         * @brief 
         * Says wether this ray can continue expanding or not.
         * @return true 
         * @return false 
         */
        bool HasEnded();

        /**
         * @brief
         * Tells the ray that it has finished expanding.
         * @return true 
         * @return false 
         */
        bool SetAsEnded();
};