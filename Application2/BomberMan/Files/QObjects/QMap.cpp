/**
 * @file QCountDownMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QMap.h"

QBomberManMap::QBomberManMap()
{
	CreateWidgets();
	CreateLayouts();
	ConnectWidgets();
	BuildWidget();

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void QBomberManMap::SetMapReference(Map* newMapRef)
{
	//Clear();
	mapRef = newMapRef;
	sizeX = mapRef->GetSizeX();
	sizeY = mapRef->GetSizeY();
	BuildFromMapRef();
}

void QBomberManMap::CreateWidgets()
{

}

void QBomberManMap::CreateLayouts()
{
	mapLayout = new QGridLayout();
	mapLayout->setSpacing(0);
	mapLayout->setSizeConstraint(QLayout::SetMaximumSize);
}

void QBomberManMap::ConnectWidgets()
{

}

void QBomberManMap::BuildWidget()
{
	setLayout(mapLayout);
}

void QBomberManMap::SetTileColor(TileTypes tile, QColor newColor)
{
	tileColors[tile] = newColor;
}

void QBomberManMap::SetScale(int newScaleX, int newScaleY)
{
	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y) {
			//QLabel* lblMapCell = new QLabel;
			//QPixmap pm(QString::fromStdString(map->tileSvg[map->GetTileDataAtPosition(x, y)]));
			//auto newPixmap = pm.scaled(50, 50);
			//lblMapCell->setPixmap(newPixmap);
	
			QLabel* label = gridContent[y][x];

			QPixmap originalPixmap(ChangeSVGColor(QString::fromStdString(mapRef->tileSvg[mapRef->GetTileDataAtPosition(x, y)]), tileColors[mapRef->GetTileDataAtPosition(x, y)]));
			int desiredWidth = newScaleX / sizeX;
			int desiredHeight = newScaleY / sizeY;
			QPixmap resizedPixmap = originalPixmap.scaled(desiredWidth, desiredHeight, Qt::KeepAspectRatio);

			// Set QLabel's size policy to stretch horizontally and vertically
			label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			label->setScaledContents(true); // Ensure the QLabel scales its contents

			// Set the resized pixmap as the QLabel's pixmap
			label->setPixmap(resizedPixmap);
		}
	}
}

void QBomberManMap::Clear()
{
	while (QLayoutItem* item = mapLayout->takeAt(0))
	{
		if (QWidget* widget = item->widget())
			widget->deleteLater();
		delete item;
	}

	//for (int x = 0; x < sizeX; ++x) {
	//	for (int y = 0; y < sizeY; ++y) {
	//		delete gridContent[y][x];
	//	}
	//}

	sizeX = 0;
	sizeY = 0;
}

void QBomberManMap::TileChanged(int x, int y, TileTypes newTile)
{
	//QPixmap pm(QString::fromStdString(mapRef->tileSvg[newTile]));
	QPixmap pm(ChangeSVGColor(QString::fromStdString(mapRef->tileSvg[newTile]), tileColors[newTile]));

	auto newPixmap = pm.scaled(scaleX, scaleY);

	if (y >= gridContent.size())
	{
		qFatal() << "y coordinate is bigger than the QVector's Y size when calling TileChanged. Y: " << QString::number(y) << ", max: " << QString::number(gridContent.size());
		return;
	}

	if (x >= gridContent[y].size())
	{
		qFatal() << "x coordinate is bigger than the QVector's X size when calling TileChanged. X: " << QString::number(x) << ", max: " << QString::number(gridContent[y].size());
		return;
	}

	// - COLOR STUFF HERE - //

	int w = scaleX;
	int h = scaleY;

	//qFatal() << QString::number(w) << ", " << QString::number(h);

	QLabel* label = gridContent[y][x];

	//QPixmap originalPixmap;
	//originalPixmap.load(QString::fromStdString(mapRef->tileSvg[newTile]));
	QPixmap originalPixmap(ChangeSVGColor(QString::fromStdString(mapRef->tileSvg[newTile]), tileColors[newTile]));


	int desiredWidth = w / sizeX;
	int desiredHeight = h / sizeY;
	QPixmap resizedPixmap = originalPixmap.scaled(desiredWidth, desiredHeight, Qt::KeepAspectRatio);

	// Set QLabel's size policy to stretch horizontally and vertically
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	label->setScaledContents(true); // Ensure the QLabel scales its contents

	// Set the resized pixmap as the QLabel's pixmap
	label->setPixmap(resizedPixmap);
}

void QBomberManMap::SetAsPaused()
{
	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y) {
			QLabel* slot = gridContent[y][x];
			slot->setEnabled(false);
		}
	}
}

void QBomberManMap::SetAsPlaying()
{
	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y) {
			QLabel* slot = gridContent[y][x];
			slot->setEnabled(true);
		}
	}
}

void QBomberManMap::SizeChanged()
{
	SetScale(width(), height());
}

void QBomberManMap::BuildFromMapRef()
{
	// 
	for (int y = 0; y < sizeY; ++y) {
		QVector<QLabel*> newVectorX;
		gridContent.push_back(newVectorX);
		for (int x = 0; x < sizeX; ++x) {
			QLabel* mapTile = new QLabel;
			gridContent[y].append(mapTile);
			mapLayout->addWidget(mapTile, y, x, 1, 1);
		}
	}

	int w = width();
	int h = height();

	scaleX = w;
	scaleY = h;
	//qFatal() << QString::number(w) << ", " << QString::number(h);

	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y) {

			// Get the QLabel to display the SVG image
			QLabel* label = gridContent[y][x];

			// Convert the SVG content to a QPixmap (PNG format)
			//QPixmap originalPixmap;
			//originalPixmap.load(QString::fromStdString(mapRef->tileSvg[mapRef->GetTileDataAtPosition(x, y)]));
			QPixmap originalPixmap(ChangeSVGColor(QString::fromStdString(mapRef->tileSvg[mapRef->GetTileDataAtPosition(x, y)]), tileColors[mapRef->GetTileDataAtPosition(x, y)]));


			// Resize the original pixmap to the desired size
			int desiredWidth = w/sizeX;
			int desiredHeight = h/sizeY;
			QPixmap resizedPixmap = originalPixmap.scaled(desiredWidth, desiredHeight, Qt::KeepAspectRatio);

			// Set QLabel's size policy to stretch horizontally and vertically
			label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			label->setScaledContents(true); // Ensure the QLabel scales its contents

			// Set the resized pixmap as the QLabel's pixmap
			label->setPixmap(resizedPixmap);
		}
	}
}