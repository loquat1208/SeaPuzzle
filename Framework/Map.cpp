#include "Map.h"
#include "Mouse.h"
#include "DxLib.h"
#include "Chip.h"

Map::Map( ) {
}

Map::~Map( ) {
}

int Map::posToIdx( int x, int y ) {
	ChipPtr chip = ChipPtr( new Chip );
	int idx_x = x / chip->getChipSize( );
	int idx_y = y / chip->getChipSize( );
	int idx = idx_x + ( idx_y - 2 ) * MAP_X_NUM; //後マジックnumber消す。
	if ( idx < 0 || idx >= MAP_MAX ) {
		idx = -1;
	}
	return idx;
}