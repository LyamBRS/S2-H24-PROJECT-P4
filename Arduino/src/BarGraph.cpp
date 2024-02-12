#include "BarGraph.h"

BarGraph(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG, int pinH, int pinI, int pinJ){
    
}

int GetBits();

bool SetBits(int newBits);

bool FlipAll();

bool TurnAllOff();

bool TurnAllOn();

bool GetIndividualState(int ledNumber);

bool SetIndividualState(int ledNumber, bool wantedState);

bool Update();