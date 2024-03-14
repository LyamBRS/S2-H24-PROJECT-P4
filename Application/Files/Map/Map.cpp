#pragma once

 // - INCLUDES - //
#include "Map.h"

 // - DEFINES - //

 // - CLASS - //

int Map::GetSizeX()
{
	return sizeX;
}

int Map::GetSizeY()
{
	return sizeY;
}

int Map::GetAmountOfPlayer()
{
	return amountOfPlayer;
}

std::string Map::GetName()
{
	return mapName;
}

Map::Map(nlohmann::json MapData)
{
	storedMapData = MapData;
	sizeX = MapData["sizeX"];
	sizeY = MapData["sizeY"];
	amountOfPlayer = MapData["amountOfPlayers"];
	mapName = MapData["name"];
	mapAsString = "NOT IMPLEMENTED";
	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			map[j][i] = MapData["map"][i][j];
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
	std::string PlayerSpawn = " 0 ";
	std::string Smoke = "%&%";
	std::string Power = " + ";

	for (int j = 0; j < sizeY; ++j) {
		for (int i = 0; i < sizeX; ++i) {
			switch (map[i][j])
			{
				case TileTypes::EMPTY:
					PrintInColour(std::cout, Empty, colors::grey, colors::black);
					break;
				case TileTypes::PERMAWALL:
					PrintInColour(std::cout, PermaWall, colors::grey, colors::grey);
					break;
				case TileTypes::WALL:
					PrintInColour(std::cout, Wall, colors::grey, colors::black);
					break;
				case TileTypes::PLAYERSPAWN:
					PrintInColour(std::cout, PlayerSpawn, colors::red, colors::black);
					break;
				case TileTypes::SMOKE:
					PrintInColour(std::cout, Smoke, colors::grey, colors::black);
					break;
				case TileTypes::POWER:
					PrintInColour(std::cout, Power, colors::yellow, colors::black);
					break;
			}
		}
		std::cout << std::endl;
	}

	return true;
}

TileTypes Map::GetTileDataAtPosition(int x, int y)
{
	return map[x][y];
}

bool Map::SetTileDataAtPosition(int x, int y, TileTypes wantedTile)
{
	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			if (i == x && j == y)
			{
				map[i][j] = wantedTile;
				return true;
			}
		}
	}
	return false;
}

bool Map::LoadMap(nlohmann::json mapAsJSON)
{
	storedMapData = mapAsJSON;
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

bool Map::GetASpawnPosition(unsigned int spawnNumber, unsigned int* resultedX, unsigned int* resultedY)
{
	*resultedX = 0;
	*resultedY = 0;
	int nbfound = 0;
	TileTypes looking = TileTypes::PLAYERSPAWN;

	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			if (map[j][i] == looking) {
				if (nbfound == spawnNumber) 
				{
					*resultedX = j;
					*resultedY = i;
					return true;
				}
				nbfound++;
			}
		}
	}
	return false;
}

nlohmann::json Map::GetCurrentMap()
{
	return storedMapData;
}