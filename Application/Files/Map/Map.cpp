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
					PrintInColour(std::cout, tileChar[TileTypes::EMPTY], colors::grey, colors::black);
					break;
				case TileTypes::PERMAWALL:
					PrintInColour(std::cout, tileChar[TileTypes::PERMAWALL], colors::grey, colors::grey);
					break;
				case TileTypes::WALL:
					PrintInColour(std::cout, tileChar[TileTypes::WALL], colors::grey, colors::black);
					break;
				case TileTypes::PLAYERSPAWN:
					PrintInColour(std::cout, tileChar[TileTypes::PLAYERSPAWN], colors::red, colors::black);
					break;
				case TileTypes::PLAYER1:
					PrintInColour(std::cout, tileChar[TileTypes::PLAYER1], PLAYER_A_COLOR, colors::black);
					break;
				case TileTypes::PLAYER2:
					PrintInColour(std::cout, tileChar[TileTypes::PLAYER2], PLAYER_B_COLOR, colors::black);
					break;
				case TileTypes::PLAYER3:
					PrintInColour(std::cout, tileChar[TileTypes::PLAYER3], PLAYER_C_COLOR, colors::black);
					break;
				case TileTypes::PLAYER4:
					PrintInColour(std::cout, tileChar[TileTypes::PLAYER4], PLAYER_D_COLOR, colors::black);
					break;
				case TileTypes::SMOKE:
					PrintInColour(std::cout, tileChar[TileTypes::SMOKE], colors::grey, colors::black);
					break;
				case TileTypes::POWER_DMG:
					PrintInColour(std::cout, tileChar[TileTypes::POWER_DMG], colors::green, colors::black);
					break;
				case TileTypes::POWER_HEART:
					PrintInColour(std::cout, tileChar[TileTypes::POWER_HEART], colors::green, colors::black);
					break;
				case TileTypes::POWER_MOREBOMB:
					PrintInColour(std::cout, tileChar[TileTypes::POWER_MOREBOMB], colors::green, colors::black);
					break;
				case TileTypes::POWER_REACH:
					PrintInColour(std::cout, tileChar[TileTypes::POWER_REACH], colors::green, colors::black);
					break;
				case TileTypes::POWER_SPEED:
					PrintInColour(std::cout, tileChar[TileTypes::POWER_SPEED], colors::green, colors::black);
					break;
				case TileTypes::BOMB:
					PrintInColour(std::cout, tileChar[TileTypes::BOMB], colors::lightred, colors::black);
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

TileTypes Map::GetTileDataAtPosition(Positions pos)
{
	return map[pos.X()][pos.Y()];
}

bool Map::SetTileDataAtPosition(int x, int y, TileTypes wantedTile)
{
	for (int j = 0; j < sizeY; ++j) {
		for (int i = 0; i < sizeX; ++i) {
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
	*resultedX = -1;
	*resultedY = -1;
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

TileTypes Map::GetPlayerTypeFromId(int playerId)
{
	switch (playerId)
	{
		case 0:
			return TileTypes::PLAYER1;
		case 1:
			return TileTypes::PLAYER2;
		case 2:
			return TileTypes::PLAYER3;
		case 3:
			return TileTypes::PLAYER4;
	default:
		break;
	}
}

nlohmann::json Map::GetCurrentMap()
{
	return storedMapData;
}