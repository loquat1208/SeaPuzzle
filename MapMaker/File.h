#pragma once
#include "smart_ptr.h"

PTR( File );

class File {
public:
	File( );
	virtual ~File( );
public:
	void save( int stage_num );
	void load( int stage_num );
};

