#include "MapMaker.h"
#include "Framework.h"
#include "DxLib.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "File.h"

const int INPUT_X = 105;
const int INPUT_Y = 100;
const int STAGE_MAX = 999;
const int STAGE_MIN = 1;

MapMakerPtr MapMaker::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< MapMaker >( fw->getTask( MapMaker::getTag( ) ) );
}

MapMaker::MapMaker( ) {
	_chip = ChipPtr( new Chip );
	_map = MapPtr( new Map );
	_file = FilePtr( new File );
	_mouse = Mouse::getTask( );
	_keyboard = Keyboard::getTask( );
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, TYPE::TYPE_OCTOPUS );
		_chip->setStatus( i, STATUS::STATUS_NONE );
	}
	_stage_num = 0;
	_state = STATE::STATE_MAPMAKER;
}

MapMaker::~MapMaker( ) {
}

void MapMaker::update( ) {
	switch ( _state ) {
	case STATE_INPUT_STAGE:
		inputStageNum( );
		break;
	case STATE_SAVE_STAGE:
		saveStage( _stage_num );
		break;
	case STATE_LOAD_STAGE:
		loadStage( _stage_num );
		break;
	case STATE_MAPMAKER:
		changeChip( );
		break;
	default:
		break;
	}

	if ( _keyboard->isPushKey( "F1" ) ) {
		_state = STATE::STATE_INPUT_STAGE;
	}
	if ( _keyboard->isPushKey( "F4" ) ) {
		_state = STATE::STATE_LOAD_STAGE;
		_file->load( _stage_num );
		loadStage( _stage_num );
	}
	if ( _keyboard->isPushKey( "F5" ) ) {
		_state = STATE::STATE_SAVE_STAGE;
		saveStage( _stage_num );
		_file->save( _stage_num );
	}
}

void MapMaker::changeChip( ) {
	if ( _mouse->getStatus( ) != 1 ) {
		return;
	}

	//違うChipをClickしたら、初期化
	int before_idx = mouse_idx;
	mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );
	if ( mouse_idx == -1 ) { //Chipじゃなかったらreturn
		return;
	}
	if ( before_idx != mouse_idx && _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			_chip->setStatus( i, STATUS::STATUS_NONE );
		}
	}

	//LockされてないChipをClickしたら、Lockする
	if ( _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		_chip->setStatus( mouse_idx, STATUS::STATUS_LOCKED );
	}
	else { //LockされたChipをClickしたら、色を変えてLockを解除
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).status != STATUS::STATUS_LOCKED ) {
				continue;
			}
			_chip->setType( i, ( TYPE ) ( ( _chip->getChip( i ).type + TYPE::TYPE_MAX - 1 ) % TYPE::TYPE_MAX ) );
			_chip->setStatus( i, STATUS::STATUS_NONE );
		}
	}
}

void MapMaker::inputStageNum( ) {
	DrawString( 0, 100, "STAGE NUM : ", GetColor( 255, 255, 255 ) );
	_stage_num = KeyInputNumber( INPUT_X, INPUT_Y, STAGE_MAX, STAGE_MIN, TRUE );

	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, TYPE::TYPE_OCTOPUS );
		_chip->setStatus( i, STATUS::STATUS_NONE );
	}
	_state = STATE::STATE_MAPMAKER;
}

void MapMaker::saveStage( int stage_num ) {
	STAGE stage;
	stage.num = _stage_num;
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		stage.chip_type[ i ] = _chip->getChip( i ).type;
	}
	data[ stage_num ] = stage;
	_state = STATE::STATE_MAPMAKER;
}

void MapMaker::loadStage( int stage_num ) {
	if ( data[ stage_num ].chip_type.empty( ) ) {
		_state = STATE::STATE_MAPMAKER;
		return;
	}
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, data[ stage_num ].chip_type[ i ] );
	}
	_state = STATE::STATE_MAPMAKER;
}

int MapMaker::getStageNum( ) {
	return _stage_num;
}

std::array< TYPE, Map::MAP_MAX > MapMaker::getChipType( int stage_num ) {
	return data[ stage_num ].chip_type;
}

void MapMaker::setChipType( int stage_num, std::array< TYPE, Map::MAP_MAX > chip_type ) {
	STAGE stage;
	stage.num = stage_num;
	stage.chip_type = chip_type;
}

ChipPtr MapMaker::getChipPtr( ) {
	return _chip;
}
