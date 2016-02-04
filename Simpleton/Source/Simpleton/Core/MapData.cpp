#include "MapData.h"

MapData::MapData()
	: mMapWidth(0)
	, mMapHeight(0)
	, mTileWidth(0)
	, mTileHeight(0)
	, mMapBuffer(nullptr)
	, mMapSize(0)
{
}

MapData::~MapData()
{
	delete mMapBuffer;
}

void MapData::LoadMap(const char* mapFile)
{
	// Construct full path name
	std::string fullPath = "../../Assets/Maps/";
	fullPath += mapFile;

	// Open the file
	std::ifstream file;
	file.open(fullPath);

	// Check if the file is openend properly
	if (file.fail())
	{
		std::cout << "Failed to open file " << fullPath << std::endl;
		return;
	}

	// Temp vars
	std::string temp;
	int tile, qty;

	// Read in Header info
	while (!file.eof())
	{
		if(file.peek() == '#' || file.peek() == 10) // 10 is the return character
		{
			getline(file, temp);
			continue;
		}

		file >> temp;

		if (temp == "tileset")
		{
			// Get filename for tileset
			file >> mFileName;
		}
		else if (temp == "mapsize")
		{
			// Get mapsize
			file >> mMapWidth >> mMapHeight;
			
			// Allocate for map buffer
			mMapSize = mMapWidth * mMapHeight;
			mMapBuffer = new int[mMapSize];
		}
		else if (temp == "tilesize")
		{
			// Get tilesize
			file >> mTileWidth >> mTileHeight;
			break;
		}
		else
		{
			// Error in file format
			std::cout << "There is an error in the file format of " << mapFile << std::endl;
		}
	}

	// Read in Body
	while (!file.eof())
	{
		if(file.peek() == '#' || file.peek() == 10) // 10 is the return character
		{
			getline(file, temp);
			continue;
		}

		file >> tile >> qty;

		for (int i = 0; i < mMapSize; ++i)
		{
			if (qty < 0) // if there is a quantity
			{
				qty = -qty;
				for (int q = 0; q < qty; ++q)
				{
					mMapBuffer[i+q] = tile;
				}
				i += qty - 1;
				file >> tile >> qty;
			}
			else // there is no quantity
			{
				mMapBuffer[i] = tile;
				tile = qty;
				file >> qty;
			}
		}
	}

	// Done
	file.close();
}