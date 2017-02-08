#include "Viewer.h"
#include "Framework.h"
#include "DxLib.h"
#include "MapMaker.h"
#include "Map.h"
#include "Chip.h"

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( Viewer::getTag( ) ) );
}

Viewer::Viewer( ) {

}

Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	drawUI( );
	drawMap( );
}

void Viewer::drawUI( ) {
	FrameworkPtr fw = Framework::getInstance( );
	MapMakerPtr map_maker = MapMaker::getTask( );
	DrawFormatString( 5, 0, 0xffffff, "F1 : Select Stage" );
	DrawFormatString( 5, 20, 0xffffff, "F4 : Load File" );
	DrawFormatString( 5, 40, 0xffffff, "F5 : Save File" );
	DrawFormatString( fw->getWindowWidth( ) - 120, 0, 0xff0000, "STAGE : %d", map_maker->getStageNum( ) );
}

void Viewer::drawMap( ) {
	MapMakerPtr map_maker = MapMaker::getTask( );
	ChipPtr chip = map_maker->getChipPtr( );
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		chip->drawChip( i, -3 );
	}
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		if ( chip->getChip( i ).status != STATUS::STATUS_NONE ) {
			chip->drawChip( i, 3 );
		}
	}
}