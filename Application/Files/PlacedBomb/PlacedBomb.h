/**
 * @file PlacedBomb.h
 * @author LyamBRS
 * @brief
 * Holds the header definition of the placebomb
 * object. Allowing bombs to be seen and interact
 * with the map.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../BaseObject/BaseObject.hpp"
#include "../SimpleTimer/SimpleTimer.h"
#include "../Map/Map.h"
#include "../Map/Utils.hpp"
#include "../Positions/Positions.h"
#include "Ray.h"
#include <vector>

// - DEFINES - //
#define BOMB_END_FRAMES 10

#define ANGLE_R 0.0f
#define ANGLE_TR 0.78f
#define ANGLE_T 1.57f
#define ANGLE_TL 2.34f
#define ANGLE_L 3.14f
#define ANGLE_BL 3.9f
#define ANGLE_B 4.71f
#define ANGLE_BR 5.49f

#define ANGLE_THRESHOLD 0.39

// - FUNCTIONS - //
float GetRaycastAngleIncrement(int bombFinalRadius);

/**
 * @brief
 * - 0: right
 * @brief
 * - 1: top right
 * @brief
 * - 2: top
 * @brief
 * - 3: top left
 * @brief
 * - 4: left
 * @brief
 * - 5: bottom left
 * @brief
 * - 6: bottom
 * @brief
 * - 7: bottom right
 * @param angle 
 * @return int 
 */
int GetAngleGenericDirection(float angle);

// - CLASS - //

/**
 * @brief 
 * This class allows bombs to be handled on
 * the map and in the game.
 * This allows a bomb with a set explosive
 * radius to be placed on the map at a
 * specified coordinate. You must specify the
 * explosive force (radius in blocks) and the
 * length of the fuse (how many updates until
 * it starts exploding)
 */
class PlacedBomb : public BaseObject
{
    private:

        /// @brief How long until the bomb starts exploding.
        SimpleTimer timeTillBoom = SimpleTimer(0);
        int endFrameCounter = BOMB_END_FRAMES;

        /// @brief The final explosion radius that the bomb will reach.
        int explosivePower = 0;

        /// @brief The current radius of the explosion. Starts at 0
        int currentExplosionRadius = 0;
        int wantedExplosionRadius = 0;
        int damage = 0;
        bool canDestroy = true;
        bool stopOnPlayers = false;

        bool isExploding = false;
        bool isExploded = false;
        bool hasFinishedFrames = false;

        bool canGo_TR = false; // Can any rays go diagonal top right
        bool canGo_TL = false; // Can any rays go diagonal top left
        bool canGo_BR = false; // Can any rays go diagonal down right
        bool canGo_BL = false; // Can any rays go diagonal down left

        bool canGo_U = false; // Can any rays go up?
        bool canGo_D = false; // Can any rays go down?
        bool canGo_L = false; // Can any rays go left?
        bool canGo_R = false; // Can any rays go right?

        Map* mapReference;

        bool UpdateRays();

        bool CheckAllRaysForCollisions();

        bool AllRaysFinished();

        TileTypes wantedTile = TileTypes::EMPTY;

        bool clearAtEnd = false;

    public:

        std::vector<Ray> rays;

        /**
         * @brief Construct a new Placed Bomb object.
         * This allows a bomb with a set explosive
         * radius to be placed on the map at a
         * specified coordinate. You must specify the
         * explosive force (radius in blocks) and the
         * length of the fuse (how many updates until
         * it starts exploding)
         * @param x
         * The position in the horizontal axis where
         * the bomb should be placed.
         * @param y
         * The position in the vertical axis where
         * the bomb should be placed.
         * @param explosiveForce
         * Radius of the final explosion.
         * @param fuseLength
         * How long until it actually detonates.
         */
        PlacedBomb(int x, int y, int explosiveForce, int fuseLength, int damagePerTick, Map* newMapReference, bool clearOnceFinished, TileTypes usedTile, bool stopOnPlayer, bool canDestroyBoxes);

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
        bool Update();

        /**
         * @brief 
         * Tells you if the bomb has finished fully
         * exploding. You then must delete this object.
         * @return true:
         * The bomb is done doing bomb shit.
         * @return false:
         * Bomb still doing bomb shit.
         */
        bool HasFinishedExploding();
        bool IsExploding();

        // Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
        Movements* GetVelocity();

        Positions* GetCurrentCoordinates();

        Positions* GetOldCoordinates();

        bool IsInsideExplosion(int x, int y);
        int GetDamagePoints();

        bool CanDestroy();

        bool Draw();
        bool Clear();
};