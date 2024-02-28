#pragma once

 // - INCLUDES - //
#include "Map.h"

 // - DEFINES - //

 // - CLASS - //

Map::Map()
{

}

bool Map::Update()
{
	return false;
}

bool Map::Draw()
{
	return false;
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

