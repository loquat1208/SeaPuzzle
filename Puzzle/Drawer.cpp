#include "Drawer.h"
#include "DxLib.h"
#include "Framework.h"
#include "Map.h"
#include "Play.h"
#include "UI.h"
#include "Scene.h"
#include "Chip.h"
#include "Select.h"

const int BG_IMG_WIDTH = 484;
const int BG_IMG_HEIGHT = 785;
const int SEEWEED_WIDTH = 30;
const int SEEWEED_HEIGHT = 120;
const int NUMBER_SIZE = 40;

const int ANI_FPS = 30;

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( Drawer::getTag( ) ) );
}

Drawer::Drawer( ) {
	_num_img = LoadGraph( "../Resources/Number.png" );
	_background_img = LoadGraph( "../Resources/Background.png" );
	_seeweed_img = LoadGraph( "../Resources/seeweed.png" );

	_play = Play::getTask( );
	_scene = Scene::getTask( );
	_map = MapPtr( new Map );
	_select = SelectPtr( new Select );

	_ani_timer = 0;
	_stage_max = _select->getIconNum( );
}

Drawer::~Drawer( ) {
}

void Drawer::update( ) {
	_ani_timer++;

	if ( _scene->getScene( ) == SCENE::SCENE_TITLE ) {
		drawTitle( );
	}
	if ( _scene->getScene( ) == SCENE::SCENE_SELECT ) {
		drawSelect( );
	}
	if ( _scene->getScene( ) == SCENE::SCENE_PLAY ) {
		drawBackground( );
		drawMap( );
		drawUI( );
	}
	if ( _scene->getScene( ) == SCENE::SCENE_FAIL ) {
		drawFail( );
	}
	if ( _scene->getScene( ) == SCENE::SCENE_CLEAR ) {
		drawClear( );
	}
}

void Drawer::drawMap( ) {
	PlayPtr play = Play::getTask( );
	ChipPtr chip = play->getChipPtr( );
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		chip->drawChip( i, -3 );
	}
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		if ( chip->getChip( i ).status != STATUS::STATUS_NONE ) {
			chip->drawChip( i, 3 );
		}
	}
}

void Drawer::drawUI( ) {
	UIPtr ui = UIPtr( new UI );
	//écÇ¡ÇΩëÄçÏâÒêîÅB
	drawNum( 18, 25, ui->canChangeNum( ) );
}

void Drawer::drawNum( int x, int y, int num ) { //å„ÅA10à»è„Ç≈Ç‡ëŒâûÇ∑ÇÈÇÊÇ§Ç…ÅB<math.h>
	DrawRectGraph( x, y, num * NUMBER_SIZE, 0, NUMBER_SIZE, NUMBER_SIZE, _num_img, TRUE, FALSE );
}

void Drawer::drawBackground( ) {
	int ani = ( _ani_timer / ANI_FPS ) % 5;
	FrameworkPtr fw = Framework::getInstance( );
	//îwåiÅB
	DrawRectExtendGraph( 0,                     0, 
						 fw->getWindowWidth( ), fw->getWindowHeight( ), 
						 0,						0, 
						 BG_IMG_WIDTH,			BG_IMG_HEIGHT, 
						 _background_img,		TRUE );

	//äCëê
	//plz magic number delete
	DrawRectExtendGraph( 10,                  fw->getWindowHeight( ) - SEEWEED_HEIGHT, 
						 SEEWEED_WIDTH + 10,  fw->getWindowHeight( ), 
						 ani * SEEWEED_WIDTH, 0, 
						 SEEWEED_WIDTH,       SEEWEED_HEIGHT, 
						 _seeweed_img,        TRUE );
	DrawRectExtendGraph( 50,                  fw->getWindowHeight( ) - SEEWEED_HEIGHT, 
						 SEEWEED_WIDTH + 50,  fw->getWindowHeight( ), 
						 ani * SEEWEED_WIDTH, SEEWEED_HEIGHT,
						 SEEWEED_WIDTH,       SEEWEED_HEIGHT, 
						 _seeweed_img,        TRUE );
	DrawRectExtendGraph( 90,                  fw->getWindowHeight( ) - SEEWEED_HEIGHT, 
						 SEEWEED_WIDTH + 90,  fw->getWindowHeight( ), 
						 ani * SEEWEED_WIDTH, SEEWEED_HEIGHT * 2, 
						 SEEWEED_WIDTH,       SEEWEED_HEIGHT, 
						 _seeweed_img,        TRUE );
}

void Drawer::drawClear( ) {
	DrawString( 0, 0, "CLEAR\nCLICK TO CONTINUE", 0xff0000 );
}

void Drawer::drawFail( ) {
	DrawString( 0, 0, "FAIL\nCLICK TO CONTINUE", 0xff0000 );
}

void Drawer::drawTitle( ) {
	DrawString( 0, 0, "TITLE\nCLICK TO START", 0xff0000 );
}

void Drawer::drawSelect( ) {
	for ( int i = 0; i < _stage_max; i++ ) {
		int x = _select->getIconPosX( i );
		int y = _select->getIconPosY( i );
		int r = Select::ICON_SIZE / 2;
		DrawCircle( x, y, r, 0xffffff, TRUE );
	}
}
