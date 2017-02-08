#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include "Chip.h"

PTR( Play );
PTR( Mouse );
PTR( Map );
PTR( Chip );
PTR( Scene );
PTR( Select );

class Play : public Task {
public:
	static const int CHANGE_MAX = 9;
public:
	static std::string getTag( ) { return "CHIPSETTING"; }
	static PlayPtr getTask( );
public:
	Play( );
	virtual ~Play( );
public:
	int getChangeNum( );
	void setInit( int stage );
	ChipPtr getChipPtr( );
private:
	bool isLockInCross( int idx );
	void update( );
	void groupLock( int idx );
private:
	MousePtr _mouse;
	MapPtr _map;
	ChipPtr _chip;
	ScenePtr _scene;
	SelectPtr _select;
	int mouse_idx;
	int _change_num;
};

