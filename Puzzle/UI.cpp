#include "UI.h"
#include "Play.h"

UI::UI( ) {
	_play = Play::getTask( );
}

UI::~UI( ) {
}

int UI::canChangeNum( ) {
	if ( _play == nullptr ) {
		return Play::CHANGE_MAX;
	}
	int can_change_num = 0;
	can_change_num = _play->getChangeNum( );
	return can_change_num;
}