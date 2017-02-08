#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include <array>
#include "Map.h"

PTR( Chip );
PTR( Mouse );
PTR( Map );

enum STATUS {
	STATUS_NONE,
	STATUS_LOCKED,
};

enum TYPE {
		TYPE_NONE,
		TYPE_A,
		TYPE_B,
		TYPE_C,
		TYPE_D,
		TYPE_E,
		TYPE_F,
		TYPE_G,
		TYPE_MAX,
};

struct CHIP {
	STATUS status;
	TYPE type;
};

class Chip : public Task {
public:
	static std::string getTag( ) { return "CHIP"; }
	static ChipPtr getTask( );
public:
	Chip();
	virtual ~Chip();
public:
	void setType( int idx, TYPE type );
	void setStatus( int idx, STATUS status );
	CHIP getChip( int idx );
private:
	void update( );
private:
	TYPE _chip;
	std::array< CHIP, Map::MAP_MAX >chip;
	int _lock_num;
	bool _lock_trigger;
	MousePtr _mouse;
	MapPtr _map;
};

