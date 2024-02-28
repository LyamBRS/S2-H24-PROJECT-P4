#include "BarGraph.h"

BarGraph::BarGraph()
{

}

BarGraph::BarGraph(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG, int pinH, int pinI, int pinJ){
    Leds[0] = new LED(pinA);
    Leds[1] = new LED(pinB);
    Leds[2] = new LED(pinC);
    Leds[3] = new LED(pinD);
    Leds[4] = new LED(pinE);
    Leds[5] = new LED(pinF);
    Leds[6] = new LED(pinG);
    Leds[7] = new LED(pinH);
    Leds[8] = new LED(pinI);
    Leds[9] = new LED(pinJ);
    canBeUsed = true;
}

int BarGraph::GetBits(){
    return bits;
}

bool BarGraph::SetBits(int newBits){
    if(!canBeUsed) return false;
    bits = newBits;
    return true;
}

bool BarGraph::FlipAll(){
    if(!canBeUsed) return false;
    bits = ~bits;
    return true;
}

bool BarGraph::TurnAllOff(){
    if(!canBeUsed) return false;
    for (int i = 0; i < 10; i++)
    {
        Leds[i]->TurnOff();
    }
    bits = 0;
    return true;
}

bool BarGraph::TurnAllOn(){
    if(!canBeUsed) return false;
    for (int i = 0; i < 10; i++)
    {
        Leds[i]->TurnOn();
    }
    bits = 0xFFFF;
    return true;
}

bool BarGraph::GetIndividualState(int ledNumber){
    if(!canBeUsed) return false;
    return Leds[ledNumber]->GetState();
}

bool BarGraph::SetIndividualState(int ledNumber, bool wantedState){
    if(!canBeUsed) return false;
    if (wantedState == true)
    {
        bits = bits | ((unsigned int)(1) << (unsigned int)(ledNumber));
    }
    else
    {
        bits = bits & ~((unsigned int)(1) << (unsigned int)(ledNumber));
    }
    return true;
}

bool BarGraph::Update(){
    if(!canBeUsed) return false;
    for(int index=0; index<10; index++)
    {
        unsigned int shiftedBits = (unsigned int)(bits) >> index;
        unsigned int result = shiftedBits & 1;
        if (result == true)
        {
            Leds[index]->TurnOn();
            Leds[index]->Update();
        }
        else
        {
            Leds[index]->TurnOff();
            Leds[index]->Update();
        }
    }
    return true;
}