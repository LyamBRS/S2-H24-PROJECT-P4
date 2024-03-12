#pragma once

 // - INCLUDES - //
#include "Map.h"

 // - DEFINES - //

 // - CLASS - //

Map::Map(nlohmann::json MapData)
{
	storedMapData = MapData;
	sizeX = MapData["sizeX"];
	sizeY = MapData["sizeY"];
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
	std::string Player = " @ ";
	std::string Smoke = "%&%";
	std::string Power = " + ";

	for (int j = 0; j < sizeY; ++j) {
		for (int i = 0; i < sizeX; ++i) {
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
				case 4:
					PrintInColour(std::cout, Smoke, colors::grey, colors::black);
					break;
				case 5:
					PrintInColour(std::cout, Power, colors::yellow, colors::black);
					break;
			}


		}
		std::cout << std::endl;
	}

	return true;
}

int Map::GetTileDataAtPosition(int x, int y)
{
	return map[x][y];
}

bool Map::SetTileDataAtPosition(int x, int y, int wantedTile)
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
	// Oublie pas de faire un struct aussi pour les tuiles.
	// Delete/Remplace les structs dans Map.h pour le tiens
	// Oublie pas de mettre genre 4 joueurs potentiels dedans as well. thx ^^
	// - faire struct  (je peut me demerder sans, mais ca vas faire dla magouille comme sans getter)
	// - faire Getters (pas urgent, mais necessaire)
	// - faire ste fonction la (test en selectionnant une map, enter, enter, enter (att la fin du decompte), check si les joueurs sont au bonne coordonnees.)
	*resultedX = 0;
	*resultedY = 0;
	return false;
}

nlohmann::json Map::GetCurrentMap()
{
	return storedMapData;
}