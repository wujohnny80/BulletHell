#ifndef _MAPDATA_H_
#define _MAPDATA_H_

#include <fstream>
#include <iostream>
#include <string>

class MapData
{
public:
	MapData();
	~MapData();

	void LoadMap(const char* mapFile);
	std::string FileName() const	{ return mFileName; }
	int* MapBuffer() const			{ return mMapBuffer; }
	int Size() const				{ return mMapSize; }
	int MapWidth() const			{ return mMapWidth; }
	int MapHeight() const			{ return mMapHeight; }
	int TileWidth() const			{ return mTileWidth; }
	int TileHeight() const			{ return mTileHeight; }

private:
	std::string mFileName;
	int mMapWidth;
	int mMapHeight;
	int mTileWidth;
	int mTileHeight;
	int* mMapBuffer;
	int mMapSize;
};

#endif //_MAPDATA_H_
