#pragma once
#include "smart_ptr.h"
#include <array>
#include "Map.h"

PTR( Chip );
PTR( Map );

enum STATUS {
	STATUS_NONE,
	STATUS_LOCKED,
};

enum TYPE {
		TYPE_NONE,
		TYPE_OCTOPUS,
		TYPE_BLOWFISH,
		TYPE_CRAB,
		TYPE_WHALE,
		TYPE_TURTLE,
		TYPE_MAX,
};

struct CHIP {
	STATUS status;
	TYPE type;
};

class Chip {
public:
	Chip( );
	virtual ~Chip( );
public:
	CHIP getChip( int idx );
	void setType( int idx, TYPE type );
	void setStatus( int idx, STATUS status );
	void drawChip( int idx, int size );
	int getChipSize( );
private:
	std::array< CHIP, Map::MAP_MAX >chip;
	int getChipIMG( TYPE type );
private:
	int _chip_img;
	int _chip_size;
	MapPtr _map;
};

