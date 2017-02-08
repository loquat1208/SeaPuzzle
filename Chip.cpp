#include "Chip.h"
#include "Framework.h"
#include "DxLib.h"
#include "Map.h"
#include "Mouse.h"


ChipPtr Chip::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Chip >( fw->getTask( Chip::getTag( ) ) );
}

Chip::Chip( ) {
	_mouse = Mouse::getTask( );
	_map = Map::getTask( );
	_lock_trigger = false;
	_lock_num = -1;

	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		chip[ i ].type = ( TYPE )( GetRand( 5 ) + 1 );
		chip[ i ].status = STATUS::STATUS_NONE;
	}
}

Chip::~Chip( ) {
}

void Chip::update( ) {
	int mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		if ( _mouse->getStatus( ) != 2 ) {
			return;
		}

		//Click‚µ‚½Chip‚¶‚á‚È‚¢Chip‚ðClick‚·‚é‚ÆLock‚ðCancle
		if ( ( mouse_idx != _lock_num ) && _lock_trigger ) {
			for ( int i = 0; i < Map::MAP_MAX; i++ ) {
				chip[ i ].status = STATUS::STATUS_NONE;
			}
			_lock_num = -1;
			_lock_trigger = false;
		}

		//Click‚µ‚½Chip‚ðLock
		if ( mouse_idx == i && chip[ i ].status != STATUS::STATUS_LOCKED ) {
			chip[ i ].status = STATUS::STATUS_LOCKED;
			_lock_num = i;
			_lock_trigger = true;
		} 
	}

	DrawFormatString( 0, 0, 0xff0000, "Map : %d", mouse_idx );
}

void Chip::setType( int idx, TYPE type ) {
	chip[ idx ].type = type;
}

void Chip::setStatus( int idx, STATUS status ) {
	chip[ idx ].status = status;
}

CHIP Chip::getChip( int idx ) {
	return chip[ idx ];
}