TEMPLATE     = vcapp
TARGET       = BomberMan
CONFIG      += warn_on qt debug windows console
SOURCES     += BomberMan.cpp Files/Application/Application.cpp Files/Arduino/Arduino.cpp Files/Colour/Colour.cpp Files/Communication/Communication.cpp Files/Controller/Controller.cpp Files/Game/Game.cpp Files/Inventory/Inventory.cpp Files/Map/Map.cpp Files/Movements/Movements.cpp Files/Object/Object.cpp Files/PlacedBomb/PlacedBomb.cpp Files/PlacedPowerUp/PlacedPowerUp.cpp Files/Player/Player.cpp Files/Positions/Positions.cpp Files/PowerUp/PowerUp.cpp Files/ScreenAttributes/ScreenAttributes.cpp Files/Serial/SerialPort.cpp Files/Serial/PortDetector.cpp Files/Tests/Tests.cpp Files/SimpleTimer/SimpleTimer.cpp Files/Application/AppHandler.cpp Files/Menus/Menu.cpp Files/Menus/ArduinoMenu.cpp Files/Menus/ExitMenu.cpp Files/Menus/MainMenu.cpp Files/Menus/TestMenu.cpp Files/Menus/MapMenu.cpp Files/Arduino/ThreadManager.cpp
HEADER      += Files/Application/Application.h Files/Arduino/Arduino.h Files/Colour/Colour.h Files/Communication/Communication.h Files/Controller/Controller.h Files/Game/Game.h Files/Inventory/Inventory.h Files/Map/Map.h Files/Movements/Movements.h Files/Object/Object.h Files/PlacedBomb/PlacedBomb.h Files/PlacedPowerUp/PlacedPowerUp.h Files/Player/Player.h Files/Positions/Positions.h Files/PowerUp/PowerUp.h Files/ScreenAttributes/ScreenAttributes.h Files/Serial/SerialPort.h Files/Serial/PortDetector.h Files/Tests/Tests.h Files/JSON/json.h Files/SimpleTimer/SimpleTimer.h Files/Application/AppHandler.h Files/Menus/Menu.h Files/Menus/ArduinoMenu.h Files/Menus/ExitMenu.h Files/Menus/MainMenu.h Files/Menus/TestMenu.h Files/Menus/MapMenu.h Files/Arduino/ThreadManager.hpp
QT          += widgets
