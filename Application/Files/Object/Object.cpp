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

        Positions* Object::GetPosition(){
            return &position;
        }

        Positions* Object::GetOldPosition(){
            return &OldPosition;
        }
