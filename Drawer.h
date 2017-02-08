#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Chip.h"
#include <string>

PTR( Drawer );
PTR( Map );
PTR( Chip );

class Drawer : public Task {
public:
	static std::string getTag( ) { return "DRAWER"; }
	static DrawerPtr getTask( );
public:
	Drawer( );
	virtual ~Drawer( );
public:
	ChipPtr _chip;
	MapPtr _map;
private:
	void update( );
	void drawMap( );
	void drawChip( int idx, int size );
	int getChipResource( TYPE type );
};

