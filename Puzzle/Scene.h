#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Scene );
PTR( Result );
PTR( Mouse );
PTR( Play );
PTR( Select );

enum SCENE {
	SCENE_TITLE,
	SCENE_SELECT,
	SCENE_PLAY,
	SCENE_FAIL,
	SCENE_CLEAR,
	SCENE_OPTION,
	SCENE_MAX,
};

class Scene : public Task {
public:
	static std::string getTag( ) { return "SCENE"; }
	static ScenePtr getTask( );
public:
	Scene( );
	virtual ~Scene( );
public:
	SCENE getScene( );
private:
	void update( );
	void titleToSelect( );
	void StageToPlay( );
	void playToFail( );
	void playToClear( );
	void failToPlay( );
	void clearToPlay( );
	void option( );
private:
	ResultPtr _result;
	MousePtr _mouse;
	SCENE _scene;
	PlayPtr _play;
	SelectPtr _select;
};

