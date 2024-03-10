#pragma once

 // - INCLUDES - //
#include "Map.h"

 // - DEFINES - //

 // - CLASS - //

Map::Map(nlohmann::json MapData)
{
	sizeX = MapData["sizeX"];
	sizeY = MapData["sizeY"];
	mapName = MapData["name"];
	mapAsString = "NOT IMPLEMENTED";
	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			map[i][j] = MapData["map"][i][j];
		}
	}
}

bool Map::Update()
{
	return false;
}

bool Map::Draw()
{	
	std::string PermaWall = "   ";
	std::string Wall = "###";
	std::string Empty = " . ";
	std::string Player = " @ ";

	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			switch (map[i][j])
			{
				case 0:
					PrintInColour(std::cout, Empty, colors::grey, colors::black);
					break;
				case 1:
					PrintInColour(std::cout, PermaWall, colors::grey, colors::grey);
					
					break;
				case 2:
					PrintInColour(std::cout, Wall, colors::grey, colors::black);
					break;
				case 3:
					PrintInColour(std::cout, Player, colors::red, colors::black);
					break;
			}


		}
		std::cout << std::endl;
	}

	return true;
}

int Map::GetTileDataAtPosition(int x, int y)
{
	return 0;
}

bool Map::SetTileDataAtPosition(int x, int y, int wantedTile)
{
	return false;
}

bool Map::LoadMap(nlohmann::json mapAsJSON)
{
	
	return true;
}

// bool Map::LoadSavedMap(std::wstring filePath)
// {
// 	return false;
// }

// bool Map::SaveCurrentMap(std::wstring filePath)
// {
// 	return false;
// }

bool Map::SetMapName(std::string newName)
{
	this->mapName = newName;
	return true;
}

