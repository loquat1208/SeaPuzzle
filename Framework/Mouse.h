#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Mouse );

class Mouse : public Task {
public:
	static std::string getTag( ) { return "MOUSE"; }
	static MousePtr getTask( );
public:
	Mouse( );
	virtual ~Mouse( );
public:
	int getPosX( );
	int getPosY( );
	int getStatus( );
	void setStatus( int state );
private:
	void update( );
private:
	int _pos_x;
	int _pos_y;
	int _key;
};

