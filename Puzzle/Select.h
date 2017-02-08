#pragma once
#include "DxLib.h"
#include "smart_ptr.h"
#include "Task.h"
#include <vector>

PTR( Select );

class Select : public Task {
public:
	static std::string getTag( ) { return "SELECT"; }
	static SelectPtr getTask( );
public:
	static const int ICON_SIZE = 48;
public:
	Select( );
	virtual ~Select( );
public:
	int getIconPosX( int idx );
	int getIconPosY( int idx );
	int getIconNum( );
	int getStage( );
	bool selectStage( );
private:
	void makeIcon( );
	void update( );
private:
	VECTOR _pos;
	int _stage;
};

