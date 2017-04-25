#include "Select.h"
#include "sstream"
#include "Framework.h"
#include "Mouse.h"
#include "Scene.h"

const int MAX_ICON_IN_LINE = 4;
const int MAX_LINE = 5;

SelectPtr Select::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Select >( fw->getTask( Select::getTag( ) ) );
}

Select::Select( ) {
	_stage = 1;
}

Select::~Select( ) {
}

void Select::update( ) {
	
}

void Select::makeIcon( ) {

}

int Select::getStage( ) {
	return _stage;
}

bool Select::selectStage( ) {
	MousePtr _mouse = Mouse::getTask( );
	for ( int i = 0; i < getIconNum( ); i++ ) {
		bool x_min = _mouse->getPosX( ) > getIconPosX( i ) - Select::ICON_SIZE / 2;
		bool x_max = _mouse->getPosX( ) < getIconPosX( i ) + Select::ICON_SIZE / 2;
		bool y_min = _mouse->getPosY( ) > getIconPosY( i ) - Select::ICON_SIZE / 2;
		bool y_max = _mouse->getPosY( ) < getIconPosY( i ) + Select::ICON_SIZE / 2;
		if ( x_min && x_max && y_min && y_max ) {
			_stage = i + 1;
			return true;
		}
	}
	return false;
}

int Select::getIconPosX( int idx ) {
	FrameworkPtr fw = Framework::getInstance( );
	int dis = fw->getWindowWidth( ) / ( MAX_ICON_IN_LINE + 1 );
	int x = dis * ( idx % MAX_ICON_IN_LINE ) + dis;
	return x;
}

int Select::getIconPosY( int idx ) {
	FrameworkPtr fw = Framework::getInstance( );
	int dis = fw->getWindowHeight( ) / ( MAX_LINE + 1 );
	int y = dis * ( idx / MAX_ICON_IN_LINE ) + dis;
	return y;
}

int Select::getIconNum( ) {
	FILE *fh;

	std::string         filename;
	std::ostringstream  ost;
	int i = 1;
	while ( 1 ) {
		filename.clear( );
		ost.str( "" );
		ost << i;
		filename += "../Data/Map/" + ost.str( ) + ".map";
		errno_t err = fopen_s( &fh, filename.c_str( ), "rb" );
		if ( err != 0 ) {
			break;
		}
		i++;
	}

	return i - 1;
}
