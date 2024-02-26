#include "Object.hpp"

        Object::Object(){
            position.SetNewCoordinates(0,0);
            movement.ResetDeltas();
        }

        ScreenAttributes* Object::GetScreenAttributes(){
            return &displayAttributes;
        }

        Movements* Object::GetMovement(){
            return &movement;
        }

        /**
         * @brief Get the Position object
         * Simply returns a pointer to this objects
         * position attribute class.
         * @return Positions* 
         */
        Positions* Object::GetPosition(){
            return &position;
        }

        Positions* Object::GetOldPosition(){
            return &OldPosition;
        }
