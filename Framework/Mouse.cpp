#include "Mouse.h"
#include "Framework.h"
#include "DxLib.h"

MousePtr Mouse::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Mouse >( fw->getTask( Mouse::getTag( ) ) );
}

Mouse::Mouse( ) {
	_pos_x = 0;
	_pos_y = 0;
	_key = 0;
}

Mouse::~Mouse( ) {
}

void Mouse::update( ) {
	GetMousePoint( &_pos_x, &_pos_y );

	if ( ( GetMouseInput( ) & MOUSE_INPUT_LEFT ) != 0 ) {
		_key++;
	}
	else {
		_key = 0;
	}
}

int Mouse::getPosX( ) {
	return _pos_x;
}

int Mouse::getPosY( ) {
	return _pos_y;
}

int Mouse::getStatus( ) {
	return _key;
}

void Mouse::setStatus( int state ) {
	 _key = state;
}