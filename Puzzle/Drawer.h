#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Play.h"
#include <string>

PTR( Drawer );
PTR( Map );
PTR( Play );
PTR( Scene );
PTR( Select );

class Drawer : public Task {
public:
	static std::string getTag( ) { return "DRAWER"; }
	static DrawerPtr getTask( );
public:
	Drawer( );
	virtual ~Drawer( );
private:
	void update( );
	void drawMap( );
	void drawUI( );
	void drawBackground( );
	void drawNum( int x, int y, int num );
	void drawClear( );
	void drawFail( );
	void drawTitle( );
	void drawSelect( );
private:
	PlayPtr _play;
	MapPtr _map;
	ScenePtr _scene;
	SelectPtr _select;
private:
	int _num_img;
	int _background_img;
	int _seeweed_img;
	int _ani_timer;
	int _stage_max;
};

