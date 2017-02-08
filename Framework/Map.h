#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Map );
PTR( Mouse );

class Map {
public:
	static const int MAP_X_NUM = 7;
	static const int MAP_Y_NUM = 9;
	static const int MAP_MAX = MAP_X_NUM * MAP_Y_NUM;
public:
	Map( );
	virtual ~Map( );
public:
	int posToIdx( int x, int y );
};

