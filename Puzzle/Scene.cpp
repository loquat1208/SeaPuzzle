#include "Scene.h"
#include "Framework.h"
#include "Result.h"
#include "Mouse.h"
#include "Play.h"
#include "Select.h"

ScenePtr Scene::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Scene >( fw->getTask( Scene::getTag( ) ) );
}

Scene::Scene( ) {
	_result = ResultPtr( new Result );
	_mouse = Mouse::getTask( );
	_select = SelectPtr( new Select );

	_scene = SCENE::SCENE_TITLE;
} 

Scene::~Scene( ) {
}

void Scene::update( ) {
	switch ( _scene ) {
	case SCENE::SCENE_TITLE:
		if ( _mouse->getStatus( ) != 1 ) {
			return;
		}
		_scene = SCENE::SCENE_SELECT;
		break;
	case SCENE::SCENE_SELECT:
		if ( _mouse->getStatus( ) != 1 ) {
			return;
		}
		if ( !_select->selectStage( ) ) {
			break;
		}
		_play = Play::getTask( );
		_play->setInit( _select->getStage( ) );
		_scene = SCENE::SCENE_PLAY;
		break;
	case SCENE::SCENE_PLAY:
		if ( _result->isFail( ) ) {
			_scene = SCENE::SCENE_FAIL;
		}
		if ( _result->isClear( TYPE::TYPE_NONE ) ) {
			_scene = SCENE::SCENE_CLEAR;
		}
		break;
	case SCENE::SCENE_FAIL:
		if ( _mouse->getStatus( ) != 1 ) {
			return;
		}
		_scene = SCENE::SCENE_TITLE;
		break;
	case SCENE::SCENE_CLEAR:
		if ( _mouse->getStatus( ) != 1 ) {
			return;
		}
		_scene = SCENE::SCENE_TITLE;
		break;
	default:
		break;
	}
}

SCENE Scene::getScene( ) {
	return _scene;
}

void Scene::option( ) {
	if ( _mouse->getStatus( ) >= 2 ) {
		_scene = SCENE::SCENE_PLAY;
	}
}