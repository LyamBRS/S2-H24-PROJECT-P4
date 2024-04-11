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
    void BuildFromMapRef();


    std::map<TileTypes, QColor> tileColors =
    {
        { TileTypes::EMPTY,                 QColor(0, 0, 0)},
        { TileTypes::PERMAWALL,             QColor(255, 0, 0)},
        { TileTypes::WALL,                  QColor(255, 0, 0)},
        { TileTypes::PLAYERSPAWN,           QColor(255, 0, 0)},
        { TileTypes::SMOKE,                 QColor(255, 0, 0)},
        { TileTypes::SMOKE1,                QColor(255, 0, 0)},
        { TileTypes::SMOKE2,                QColor(255, 0, 0)},
        { TileTypes::SMOKE3,                QColor(255, 0, 0)},
        { TileTypes::SMOKE4,                QColor(255, 0, 0)},
        { TileTypes::SMOKE5,                QColor(255, 0, 0)},
        { TileTypes::POWER_HEART,           QColor(255, 0, 0)},
        { TileTypes::POWER_DMG,             QColor(255, 0, 0)},
        { TileTypes::POWER_MOREBOMB,        QColor(255, 0, 0)},
        { TileTypes::POWER_REACH,           QColor(255, 0, 0)},
        { TileTypes::POWER_SPEED,           QColor(255, 0, 0)},
        { TileTypes::PLAYER1,               QColor(255, 0, 0)},
        { TileTypes::PLAYER2,               QColor(255, 0, 0)},
        { TileTypes::PLAYER3,               QColor(255, 0, 0)},
        { TileTypes::PLAYER4,               QColor(255, 0, 0)},
        { TileTypes::POWER_BOMB_OF_WALLS,   QColor(255, 0, 0)},
        { TileTypes::POWER_DEPLOYABLE_WALL, QColor(255, 0, 0)},
        { TileTypes::BOMB,                  QColor(255, 0, 0)}
    };

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

	void CreateWidgets();
	void CreateLayouts();
	void ConnectWidgets();
	void BuildWidget();

    

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