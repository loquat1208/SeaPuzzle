#pragma once
#include "smart_ptr.h"
#include "Task.h"
#include <string>
#include <map>

PTR( Framework );
PTR( Task );

class Framework {
public:
	static FrameworkPtr getInstance( );
	static void initialize( );
	static void finalize( );
public:
	Framework( );
	virtual ~Framework( );
public:
	void run( );
	void addTask( std::string tag, TaskPtr task );
	TaskPtr getTask( std::string type );
	int getWindowWidth( );
	int getWindowHeight( );
private:
	static FrameworkPtr _instance;
	int _screen_width;
	int _screen_height;
	std::map< std::string, TaskPtr > _task_map;
};

