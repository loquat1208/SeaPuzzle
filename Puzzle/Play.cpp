#include "Play.h"
#include "Framework.h"
#include "DxLib.h"
#include "Map.h"
#include "Mouse.h"
#include "Scene.h"
#include "Chip.h"
#include "Select.h"
#include "sstream"

PlayPtr Play::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Play >( fw->getTask( Play::getTag( ) ) );
}

Play::Play( ) {
	_mouse = Mouse::getTask( );
	_map = MapPtr( new Map );
	_chip = ChipPtr( new Chip );
	_scene = Scene::getTask( );
	_select = Select::getTask( );

	setInit( _select->getStage( ) );
}

Play::~Play( ) {
}

void Play::update( ) {
	if ( _scene->getScene( ) == SCENE::SCENE_SELECT ) {
		if ( !_select->selectStage( ) ) {
			return;
		}
		setInit( _select->getStage( ) );
	}
	if ( _scene->getScene( ) != SCENE::SCENE_PLAY ) {
		return;
	}
	if ( _mouse->getStatus( ) != 1 ) {
		return;
	}

	int before_idx = mouse_idx;
	mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );

	//Chipじゃなかったらreturn
	if ( mouse_idx == -1 ) {
		return;
	}
	//TYPE_NONEだったらreturn
	if ( _chip->getChip( mouse_idx ).type == TYPE::TYPE_NONE ) {
		return;
	}
	//違うChipをClickしたら、初期化
	if ( before_idx != mouse_idx && _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			_chip->setStatus( i, STATUS::STATUS_NONE );
		}
	}
	//LockされてないChipをClickしたら、Lockする
	if ( _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		_chip->setStatus( mouse_idx, STATUS::STATUS_LOCKED );
		groupLock( mouse_idx );
	}
	//LockされたChipをClickしたら、色を変えてLockを解除
	else {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).status != STATUS::STATUS_LOCKED ) {
				continue;
			}
			_chip->setType( i, ( TYPE ) ( ( _chip->getChip( i ).type + 1 ) % TYPE::TYPE_MAX ) );
			_chip->setStatus( i, STATUS::STATUS_NONE );
			if ( _chip->getChip( i ).type == TYPE::TYPE_NONE ) {
				_chip->setType( i, TYPE::TYPE_OCTOPUS );
			}
		}
		_change_num++;
	}
}

bool Play::isLockInCross( int idx ) {
	//右を検査
	if ( idx % Map::MAP_X_NUM != ( Map::MAP_X_NUM - 1 ) ) {
		if ( _chip->getChip( idx + 1 ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//左を検査
	if ( idx % Map::MAP_X_NUM != 0 ) {
		if ( _chip->getChip( idx - 1 ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//上を検査
	if ( idx >= Map::MAP_X_NUM ) {
		if ( _chip->getChip( idx - Map::MAP_X_NUM ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//下を検査
	if ( idx < Map::MAP_MAX - Map::MAP_X_NUM ) {
		if ( _chip->getChip( idx + Map::MAP_X_NUM ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	return false;
}

void Play::groupLock( int idx ) {
	for ( int j = 0; j < Map::MAP_X_NUM + Map::MAP_Y_NUM; j++ ) { //無駄にメモリ使っている。直す必要がある。
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).type != _chip->getChip( idx ).type ) {
				continue;
			}
			if ( isLockInCross( i ) ) {
				_chip->setStatus( i, STATUS::STATUS_LOCKED );
			}
		}
	}
}

void Play::setInit( int stage ) {
	FILE *fh;

	std::string         filename;
	std::ostringstream  ost;

	filename.clear( );
	ost.str( "" );
	ost << stage;
	filename += "../Data/Map/" + ost.str( ) + ".map";
	errno_t err = fopen_s( &fh, filename.c_str( ), "rb" );
	if ( err != 0 ) {
		return;
	}

	std::array< TYPE, Map::MAP_MAX > data;
	fread( &data, sizeof( data ), 1, fh );

	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, data[ i ] );
		_chip->setStatus( i, STATUS::STATUS_NONE );
	}
	fclose( fh );

	_change_num = 0;
}

int Play::getChangeNum( ) {
	return CHANGE_MAX - _change_num;
}

ChipPtr Play::getChipPtr( ) {
	return _chip;
}
