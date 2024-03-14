#include "ScreenAttributes.h"

        ScreenAttributes::ScreenAttributes(std::string wantedASCII, int wantedColour){
            ascii = wantedASCII;
            colour = wantedColour;
        }

        std::string ScreenAttributes::Ascii(){
            return ascii;
        }

        std::string ScreenAttributes::Ascii(std::string newAscii){
            ascii = newAscii;
            return ascii;
        }

        int ScreenAttributes::Colour(){
            return colour;
        }

        int ScreenAttributes::Colour(int newColour){
            colour = newColour;
            return colour;
        }

        ScreenAttributes::ScreenAttributes()
        {
            colour = 0;
            ascii = "";
        }