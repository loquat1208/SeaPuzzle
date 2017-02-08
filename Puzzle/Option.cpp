#include "Option.h"
#include "Mouse.h"

const int OPTION_X = 300;
const int OPTION_Y = 100;
const int OPTION_SIZE = 50;

Option::Option( ) {
}


Option::~Option( ) {
}

bool Option::isClicked( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->getPosX( ) < OPTION_X ) {
		return false;
	}
	if ( mouse->getPosX( ) > OPTION_X + OPTION_SIZE ) {
		return false;
	}
	if ( mouse->getPosY( ) < OPTION_Y ) {
		return false;
	}
	if ( mouse->getPosY( ) > OPTION_X + OPTION_SIZE ) {
		return false;
	}
	return true;
}
