#include "Framework.h"
#include "UI.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Play.h"
#include "Scene.h"
#include "Select.h"

void main( ) {
    FrameworkPtr fw = Framework::getInstance( );

    TaskPtr mouse = MousePtr( new Mouse );
    fw->addTask( Mouse::getTag( ), mouse );

    TaskPtr scene = ScenePtr( new Scene );
    fw->addTask( Scene::getTag( ), scene );

	TaskPtr select = SelectPtr( new Select );
	fw->addTask( Select::getTag( ), select );

	TaskPtr play = PlayPtr(new Play);
	fw->addTask(Play::getTag(), play);

    TaskPtr drawer = DrawerPtr( new Drawer );
    fw->addTask( Drawer::getTag( ), drawer );
}
