#pragma once
#include "smart_ptr.h"
#include <string>
#include "Task.h"

PTR( Viewer );

class Viewer : public Task {
public:
	static std::string getTag( ) { return "VIEWER"; }
	static ViewerPtr getTask( );
public:
	Viewer( );
	virtual ~Viewer( );
private:
	void update( );
	void drawUI( );
	void drawMap( );
};

