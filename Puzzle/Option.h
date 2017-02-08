#pragma once
#include "smart_ptr.h"

PTR( Option );

class Option {
public:
	Option( );
	virtual ~Option( );
public:
	bool isClicked( );
private:
};

