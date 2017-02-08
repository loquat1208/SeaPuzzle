#pragma once
#include "smart_ptr.h"
#include <string>

PTR( UI );
PTR( Play );

class UI {
public:
	UI( );
	virtual ~UI( );
public:
	int canChangeNum( );
private:
	PlayPtr _play;
};

