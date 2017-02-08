#include "Chip.h"
#include "DxLib.h"
#include "Map.h"
#include "Framework.h"

const int CHIP_IMG_SIZE = 60;

Chip::Chip( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_chip_size = fw->getWindowWidth( ) / Map::MAP_X_NUM;
	_map = MapPtr( new Map );
	_chip_img = LoadGraph( "../Resources/Chip.png" );
}

Chip::~Chip( ) {
}

void Chip::drawChip( int idx, int size ) {
	TYPE type = chip[ idx ].type;
	int x = ( idx % Map::MAP_X_NUM ) * _chip_size;
	int y = ( idx / Map::MAP_X_NUM ) * _chip_size + _chip_size * 2;//後マジックnumber消す。
	int r = size;
	DrawRectExtendGraph( x - size,              y - size, 
						 x + _chip_size + size,	y + _chip_size + size, 
						 getChipIMG( type ),    0, 
						 CHIP_IMG_SIZE,         CHIP_IMG_SIZE, 
						 _chip_img,             TRUE );
}

int Chip::getChipIMG( TYPE type ) {//後、STL::mapで変える。
	FrameworkPtr fw = Framework::getInstance( );
	switch ( type ) {
	case TYPE::TYPE_OCTOPUS:
		return 1 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_BLOWFISH:
		return 2 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_CRAB:
		return 3 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_WHALE:
		return 4 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_TURTLE:
		return 5 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	default:
		return 0xffffff;
		break;
	}
}

CHIP Chip::getChip( int idx ) {
	return chip[ idx ];
}

void Chip::setType( int idx, TYPE type ) {
	chip[ idx ].type = type;
}

void Chip::setStatus( int idx, STATUS status ) {
	chip[ idx ].status = status;
}

int Chip::getChipSize( ) {
	return _chip_size;
}
