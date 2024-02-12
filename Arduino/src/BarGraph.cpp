#include "BarGraph.h"

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

}

int BarGraph::GetBits(){
    return bits;
}

bool BarGraph::SetBits(int newBits){
    bits = newBits;
    return true;
}

bool BarGraph::FlipAll(){
    for(int i=0; i<10; i++){
        if(Leds[i]->GetState() == true){
            Leds[i]->TurnOff();
        }else{
            Leds[i]->TurnOn();
        }
    }
    return true;
}

bool BarGraph::TurnAllOff(){
    for (int i = 0; i < 10; i++)
    {
        Leds[i]->TurnOff();
    }
    
    return true;
}

bool BarGraph::TurnAllOn(){
    for (int i = 0; i < 10; i++)
    {
        Leds[i]->TurnOn();
    }
    return true;
}

bool BarGraph::GetIndividualState(int ledNumber){
    return Leds[ledNumber]->GetState();
}

bool BarGraph::SetIndividualState(int ledNumber, bool wantedState){
    if (wantedState==true){
        Leds[ledNumber]->TurnOn();
    }else{
        Leds[ledNumber]->TurnOff();
    }
}

bool BarGraph::Update(){
    for(int index=0; index<16; index++)
    {
        unsigned int shiftedBits = bits >> index;
        unsigned int result = shiftedBits & 1;
        if (result==true){
            Leds[index]->TurnOn();
        }else{
            Leds[index]->TurnOff();
        }
    }
}