#include "Result.h"
#include "UI.h"
#include "Chip.h"
#include "Play.h"
#include "Map.h"
#include "Mouse.h"
#include "Select.h"

Result::Result( ) {
	_ui = UIPtr( new UI );
}

Result::~Result( ) {
}

bool Result::isFail( ) {
	MousePtr mouse = Mouse::getTask( );
	SelectPtr select = Select::getTask( );
	PlayPtr play = Play::getTask( );
	if ( play->getChangeNum( ) <= 0 ) {
		play->setInit( select->getStage( ) );
		return true;
	}
	return false;
}

bool Result::isClear( TYPE goal_type ) {
	MousePtr mouse = Mouse::getTask( );
	SelectPtr select = Select::getTask( );
	PlayPtr play = Play::getTask( );
	ChipPtr chip = play->getChipPtr( );
	if ( _ui->canChangeNum( ) < 0 ) {
		return false;
	}
	if ( goal_type == TYPE::TYPE_NONE ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( chip->getChip( i ).type != chip->getChip( 0 ).type ) {
				return false;
			}
		}
	} else {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( chip->getChip( i ).type != goal_type ) {
				return false;
			}
		}
	}
	play->setInit( select->getStage( ) );
	return true;
}
