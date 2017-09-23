#pragma once

#include "Manager.h"

class CTile : public CManager<CTile>
{
private :
	class TileData
	{
	public :
		INT X, Y;
		INT Number;
		TileData(int _x = 0, int _y = 0, int _number = 0)
			: X(_x), Y(_y), Number(_number)
		{}
	};
	vector<TileData> Tile;
	string TileName;
public :
	CTile();
	~CTile();
public :
	void TileLoad(const char * Path);
	void MakeMap();
};

