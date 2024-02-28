/**
 * @file Communication.cpp
 * @author LyamBRS
 * @brief 
 * File containing the program executed inside
 * of the Communication class.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Communication.h"

// - PROGRAM - //

/**
 * @brief 
 * Simple private function that reads
 * the data that is available on the
 * serial port and parses it into JSON
 * formats allowing us to later read it
 * normally without issues.
 * @return true:
 * Successfully parsed received message
 * into the class.
 * @return false:
 * Failed to parse the received message
 * into the class.
 */
bool Communication::ParseReceivedMessage()
{
    StaticJsonDocument<500> doc;
    JsonVariant parse_msg;

    // Gets potential JSON parsing errors.
    DeserializationError error = deserializeJson(doc, currentMessage);
    //Serial.println(currentMessage);
    currentMessage = "";
    shouldRead_ = false;

    // Raise concerns if an error prevents the JSON from being read.
    if (error) {
        Serial1.print("deserialize() failed: ");
        Serial1.println(error.c_str());
        if(errorMessage == CE_NO_ERRORS)
        {
            errorMessage = CE_PARSING_FAILED;
        }
        return false;
    }

    if(errorMessage == CE_PARSING_FAILED)
    {
        errorMessage = CE_NO_ERRORS;
    }

    // - BAR GRAPHS - //
    parse_msg = doc[CA_BAR_GRAPH_A];
    if (!parse_msg.isNull()) {
        controllerPlayerA->GetBarGraph()->SetBits(doc[CA_BAR_GRAPH_A].as<int>());
    }

    parse_msg = doc[CA_BAR_GRAPH_B];
    if (!parse_msg.isNull()) {
        controllerPlayerB->GetBarGraph()->SetBits(doc[CA_BAR_GRAPH_B].as<int>());
    }

    // - LCD - //
    parse_msg = doc[CA_LCD_MESSAGE];
    if (!parse_msg.isNull()) {
        Serial1.println(doc[CA_LCD_MESSAGE].as<String>());
        PCMessage = doc[CA_LCD_MESSAGE].as<String>();
    }

    return true;
}

/**
 * @brief 
 * Method executed when the program needs
 * to send a reply back to the PC. This
 * should be executed right after message
 * received @ref ParseReceivedMessage is
 * successfully executed.
 * @return true:
 * Successfully replied a message to the
 * PC
 * @return false:
 * Failed to reply a message to the PC.
 */
bool Communication::SendMessage()
{
    StaticJsonDocument<500> doc;

    // - JOYSTICK ATTRIBUTES - //
    doc[CA_JOYSTICK_X_A] = controllerPlayerA->GetJoystick()->GetPourcentX();
    doc[CA_JOYSTICK_X_B] = controllerPlayerB->GetJoystick()->GetPourcentX();
    doc[CA_JOYSTICK_Y_A] = controllerPlayerA->GetJoystick()->GetPourcentY();
    doc[CA_JOYSTICK_Y_B] = controllerPlayerB->GetJoystick()->GetPourcentY();
    doc[CA_JOYSTICK_BUTTON_A] = controllerPlayerA->GetJoystick()->GetButtonState();
    doc[CA_JOYSTICK_BUTTON_B] = controllerPlayerB->GetJoystick()->GetButtonState();

    // - ACCELEROMETER ATTRIBUTES - //
    doc[CA_ACCELEROMETER_X_A] = controllerPlayerA->GetAccelerometer()->GetPourcentX();
    doc[CA_ACCELEROMETER_X_B] = controllerPlayerB->GetAccelerometer()->GetPourcentX();
    doc[CA_ACCELEROMETER_Y_A] = controllerPlayerA->GetAccelerometer()->GetPourcentY();
    doc[CA_ACCELEROMETER_Y_B] = controllerPlayerB->GetAccelerometer()->GetPourcentY();
    doc[CA_ACCELEROMETER_Z_A] = controllerPlayerA->GetAccelerometer()->GetPourcentZ();
    doc[CA_ACCELEROMETER_Z_B] = controllerPlayerB->GetAccelerometer()->GetPourcentZ();

    // - BUTTONS - //
    doc[CA_TOP_BUTTON_A]    = controllerPlayerA->GetTopButton()->GetState();
    doc[CA_BOTTOM_BUTTON_A] = controllerPlayerA->GetBottomButton()->GetState();
    doc[CA_LEFT_BUTTON_A]   = controllerPlayerA->GetLeftButton()->GetState();
    doc[CA_RIGHT_BUTTON_A]  = controllerPlayerA->GetRightButton()->GetState();

    digitalWrite(13, controllerPlayerA->GetTopButton()->GetState());

    doc[CA_TOP_BUTTON_B]    = controllerPlayerB->GetTopButton()->GetState();
    doc[CA_BOTTOM_BUTTON_B] = controllerPlayerB->GetBottomButton()->GetState();
    doc[CA_LEFT_BUTTON_B]   = controllerPlayerB->GetLeftButton()->GetState();
    doc[CA_RIGHT_BUTTON_B]  = controllerPlayerB->GetRightButton()->GetState();

    // - BAR GRAPHS - //
    doc[CA_BAR_GRAPH_A] = controllerPlayerA->GetBarGraph()->GetBits();
    doc[CA_BAR_GRAPH_B] = controllerPlayerB->GetBarGraph()->GetBits();

    // - CONTROLLER STATUS - //
    doc[CA_CONTROLLER_CONNECTED_A] = controllerPlayerA->GetDetection();
    doc[CA_CONTROLLER_CONNECTED_B] = controllerPlayerB->GetDetection();

    // - MUON DETECTOR - //
    doc[CA_DETECTED_MUONS] = randomMuonDetector->GetTotal();
    randomMuonDetector->ResetCount();

    //#define CA_LCD_MESSAGE      "LM"

    // Serialisation
    serializeJson(doc, Serial);

    // Envoie
    Serial.println();
    shouldSend_ = false;
}


/**
 * @brief Construct a new Communication object.
 * Should be done in main.cpp as a global
 * object available both to void setup and void
 * loop.
 */
Communication::Communication()
{

}

/**
 * @brief 
 * Starts Arduino serial class associated
 * with the communication protocol.
 * @param baudRate
 * Communication speeds.
 * @return true:
 * Successfully started the serial.
 * @return false:
 * Failed to start the serial.
 */
bool Communication::StartSerial(unsigned long baudRate)
{
    Serial.begin(BAUD);
    serialSetUp = true;
    return true;
}

/**
 * @brief 
 * Gives the communication class a reference
 * to the 2 remote controllers that can be
 * connected to this Arduino. This way the
 * communication class can easily build the
 * message that it needs to send to the PC
 * based on the Controllers values as well
 * as set the components on the remotes to
 * wanted values.
 * @attention
 * This needs to be executed in void setup.
 * @param controllerA
 * Controller associated with player A
 * @param controllerB
 * Controller associated with player B
 * @return true:
 * Successfully linked controllers to the
 * communication class.
 * @return false:
 * Failed to link controllers.
 */
bool Communication::LinkControllers(Controller* controllerA, Controller* controllerB)
{
    controllerPlayerA = controllerA;
    controllerPlayerB = controllerB;
    controllersLinked = true;
    return true;
}

/**
 * @brief 
 * Links the muon detector to the communication
 * class allowing it to build TX messages with
 * its parameters inside.
 * @attention
 * MUST BE CALLED IN VOID SETUP
 * @param muonDetector
 * Muon detector class to link with the
 * communication class.
 * @return true:
 * Successfully linked the muon detector.
 * @return false:
 * Failed to link the muon detector.
 */
bool Communication::LinkMuonDetector(MuonDetector* muonDetector)
{
    randomMuonDetector = muonDetector;
    muonDetectorLinked = true;
    return true;
}

/**
 * @brief 
 * Method that should be executed along with
 * all the update methods of the program.
 */
void Communication::Update()
{
    static bool wasReading = false;
    static int giveUpCounter = 0;

    if(!controllersLinked)
    {
        errorMessage = CE_CONTROLLER_LINKAGE_FAILURE;
        return;
    }

    if(!serialSetUp)
    {
        errorMessage = CE_SERIAL_NOT_SETUP;
        return;
    }

    if(!muonDetectorLinked)
    {
        errorMessage = CE_MUON_DETECTOR_LINKAGE_FAILURE;
        return;
    }

    if((millis() - millisWhenLastRead) > MS_BEFORE_CONNECTION_LOST)
    {
        errorMessage = CE_COMMUNICATION_LOST;
    }

    //if(timeBetweenReadChecks.TimeLeft() == 0)
    //{
        // Check if we are receiving messages at the moment
        bool result = HasReceivedAMessage();
        giveUpCounter++;
        // We finished reading a message because we were previously reading and we aint no more.
        if(result || giveUpCounter>100)
        {
            giveUpCounter = 0;
            if(result)
            {
                millisWhenLastRead = millis();
            }
            wasReading = false;
            if(!ParseReceivedMessage()) {
                return;
            }
            if(!SendMessage())          
            {
                return;
            }
            errorMessage = CE_NO_ERRORS;  
        }

        // We are not reading and we weren't previously.
    //}

    //if(shouldRead_) // Communication received on serial port.
    //{
    //    millisWhenLastRead = millis();
    //    if(!ParseReceivedMessage()) {return;}
    //    if(!SendMessage())          {return;}
    //    errorMessage = CE_NO_ERRORS;
    //}
}

/**
 * @brief 
 * Tells you if you are actively receiving a message or not
 * @return true:
 * A is being received
 * @return false:
 * No message is being received.
 */
bool Communication::HasReceivedAMessage()
{
    static bool receiving = false;
    String parsedMessage = "";
    currentAmountOfCharacters = Serial.available();
    
    if(currentAmountOfCharacters == 0)
    {
        return false;
    }

    if(errorMessage == CE_COMMUNICATION_LOST)
    {
        errorMessage = CE_NO_ERRORS;
    }

    // CLEAR SERIAL PORT
    while(Serial.available())
    {
        int byte = Serial.read();

        if(byte < 32 || byte > 127)
        {
        }
        else
        {
            // New message is seen despite never seing the end of the other one
            if(receiving && (byte == '{'))
            {
                currentMessage = "";
                parsedMessage = "";
            }

            // The start of a fresh new message is seen
            if(!receiving && (byte == '{'))
            {
                receiving = true;
            }

            // In the middle of receiving the message
            if(receiving)
            {
                parsedMessage += ((char)byte);
            }

            // The end of the message is received.
            if(receiving && (byte == '}'))
            {
                receiving = false;
                currentMessage += parsedMessage;

                while(Serial.available())
                {
                    Serial.read();
                }

                return true;
            }
        }
    }

    currentMessage += parsedMessage;
    return false;
}

/**
 * @brief
 * Function that is required to be called
 * in @ref serialEvent
 */
void Communication::SerivalEventHandler()
{
    if(errorMessage == CE_COMMUNICATION_LOST)
    {
        errorMessage = CE_NO_ERRORS;
    }
    shouldRead_ = true;
}

/**
 * @brief
 * Tells you if there is an ongoing
 * communication problem of any sorts.
 * @attention
 * Error messages will always be 20 chars
 * long.
 * @return string 
 */
String Communication::GetErrorMessage()
{
    return errorMessage;
}

/**
 * @brief 
 * Returns the message that the PC wants written on
 * the LCD of the arduino.
 */
String Communication::GetPCMessage()
{
    return PCMessage;
}