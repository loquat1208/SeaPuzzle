#include "Framework.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Viewer.h"
#include "MapMaker.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance( );

	TaskPtr mouse = MousePtr( new Mouse );
	fw->addTask( Mouse::getTag( ), mouse );

	TaskPtr keyboard = KeyboardPtr( new Keyboard );
	fw->addTask( Keyboard::getTag( ), keyboard );

	TaskPtr map_maker = MapMakerPtr( new MapMaker );
	fw->addTask( MapMaker::getTag( ), map_maker );

	TaskPtr viewer = ViewerPtr( new Viewer );
	fw->addTask( Viewer::getTag( ), viewer );
}