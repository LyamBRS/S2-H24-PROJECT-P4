/**
 * @file QMap.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-10
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QtWidgets>
#include "../Application/AppHandler.h"
#include "../Map/Map.h"

// - DEFINES - //

// - CLASS - //

class QBomberManMap : public QWidget
{
	Q_OBJECT
	
public:
	QBomberManMap();

	void SetMapReference(Map* newMapRef);
	void SetTileColor(TileTypes tile, QColor newColor);
	void SetScale(int newScaleX, int newScaleY);
	void Clear();

    void SetAsPaused();
    void SetAsPlaying();
    void SizeChanged();

public slots:
	void TileChanged(int x, int y, TileTypes newTile);

protected:
    void resizeEvent(QResizeEvent* event) override {
        // Call base class implementation
        QWidget::resizeEvent(event);

        // Custom action when widget is resized
        //qFatal() << "Widget resized to:" << event->size();
        //SizeChanged();
    }

private:
	void BuildFromMapRef();

	void CreateWidgets();
	void CreateLayouts();
	void ConnectWidgets();
	void BuildWidget();

    std::map<TileTypes, QColor> tileColors =
    {
        { TileTypes::EMPTY,                 QColor(0, 0, 0)},
        { TileTypes::PERMAWALL,             QColor(0, 0, 0)},
        { TileTypes::WALL,                  QColor(0, 0, 0)},
        { TileTypes::PLAYERSPAWN,           QColor(0, 0, 0)},
        { TileTypes::SMOKE,                 QColor(0, 0, 0)},
        { TileTypes::SMOKE1,                QColor(0, 0, 0)},
        { TileTypes::SMOKE2,                QColor(0, 0, 0)},
        { TileTypes::SMOKE3,                QColor(0, 0, 0)},
        { TileTypes::SMOKE4,                QColor(0, 0, 0)},
        { TileTypes::SMOKE5,                QColor(0, 0, 0)},
        { TileTypes::POWER_HEART,           QColor(0, 0, 0)},
        { TileTypes::POWER_DMG,             QColor(0, 0, 0)},
        { TileTypes::POWER_MOREBOMB,        QColor(0, 0, 0)},
        { TileTypes::POWER_REACH,           QColor(0, 0, 0)},
        { TileTypes::POWER_SPEED,           QColor(0, 0, 0)},
        { TileTypes::PLAYER1,               QColor(0, 0, 0)},
        { TileTypes::PLAYER2,               QColor(0, 0, 0)},
        { TileTypes::PLAYER3,               QColor(0, 0, 0)},
        { TileTypes::PLAYER4,               QColor(0, 0, 0)},
        { TileTypes::POWER_BOMB_OF_WALLS,   QColor(0, 0, 0)},
        { TileTypes::POWER_DEPLOYABLE_WALL, QColor(0, 0, 0)},
        { TileTypes::BOMB,                  QColor(0, 0, 0)}
    };

  /*  std::map<TileTypes, QColor> tileColors =
    {
        { TileTypes::EMPTY,                QColor(0,0,0)},
        { TileTypes::PERMAWALL,            QColor(0,0,0)},
        { TileTypes::WALL,                 QColor(199, 122, 34)},
        { TileTypes::PLAYERSPAWN,          QColor(255,0,0)},
        { TileTypes::SMOKE,                QColor(0,0,0)},
        { TileTypes::SMOKE1,               QColor(255,0,0)},
        { TileTypes::SMOKE2,               QColor(21, 99, 214)},
        { TileTypes::SMOKE3,               QColor(240, 233, 29)},
        { TileTypes::SMOKE4,               QColor(11, 125, 40)},
        { TileTypes::SMOKE5,               QColor(0,0,0)},
        { TileTypes::POWER_HEART,          QColor(75, 240, 10)},
        { TileTypes::POWER_DMG,            QColor(75, 240, 10)},
        { TileTypes::POWER_MOREBOMB,       QColor(75, 240, 10)},
        { TileTypes::POWER_REACH,          QColor(75, 240, 10)},
        { TileTypes::POWER_SPEED,          QColor(75, 240, 10)},
        { TileTypes::PLAYER1,              QColor(255,0,0)},
        { TileTypes::PLAYER2,              QColor(21, 99, 214)},
        { TileTypes::PLAYER3,              QColor(240, 233, 29)},
        { TileTypes::PLAYER4,              QColor(11, 125, 40)},
        { TileTypes::POWER_BOMB_OF_WALLS,  QColor(75, 240, 10)},
        { TileTypes::POWER_DEPLOYABLE_WALL,QColor(75, 240, 10)},
        { TileTypes::BOMB,                 QColor(64, 64, 64)},
    };*/

	Map* mapRef;
	int scaleX = 50;
	int scaleY = 50;
    int sizeX = 0;
    int sizeY = 0;

	AppHandler* appRef;
	Player* playerRef;

    QGridLayout* mapLayout;
    QVector<QVector<QLabel*>> gridContent;
};