#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Chip.h"
#include <string>

PTR( Result );
PTR( UI );

class Result {
public:
	Result( );
	virtual ~Result( );
public:
	bool isFail( );
	bool isClear( TYPE goal_type );
private:
	UIPtr _ui;
};

