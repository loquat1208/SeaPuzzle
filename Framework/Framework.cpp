#include "Framework.h"
#include "DxLib.h"

FrameworkPtr Framework::_instance;

void Framework::initialize( ) {
	if ( !_instance ) {
		_instance = FrameworkPtr( new Framework );
	}
}

void Framework::finalize( ) {
	if ( _instance ) {
		_instance.reset( );
	}
}

FrameworkPtr Framework::getInstance( ) {
	return _instance;
}

Framework::Framework( ) {
	int sx = GetSystemMetrics( SM_CXSCREEN );
	int sy = GetSystemMetrics( SM_CYSCREEN );

#	if FULLSCREEN
	SetGraphMode( sx, sy, 32 );
	ChangeWindowMode( FALSE );
	_screen_width = sx;
	_screen_height = sy;
#	else
	int wx = 360; //sx * 3 / 4;
	int wy = 680; //sy * 3 / 4;	
	SetGraphMode( wx, wy, 32 );
	SetWindowInitPosition( ( sx - wx ) / 2, ( sy - wy ) / 2 );
	ChangeWindowMode( TRUE );
	_screen_width = wx;
	_screen_height = wy;
#	endif

	SetWindowText( "Test" );

	if ( DxLib_Init( ) == -1 ) {
		return;
	}

	SetDrawScreen( DX_SCREEN_BACK );
}


Framework::~Framework( ) {
	DxLib_End( );
}

void Framework::run( ) {
	while ( true ) {
		if ( ProcessMessage( ) == -1 ) {
			break;
		}
		if ( CheckHitKey( KEY_INPUT_ESCAPE ) ) {
			break;
		}

		// ƒ^ƒXƒN‚ð‰ñ‚·
		std::map< std::string, TaskPtr >::iterator it = _task_map.begin( );
		while ( it != _task_map.end( ) ) {
			TaskPtr task = it->second;
			task->update( );
			it++;
		}

		ScreenFlip( );
		ClearDrawScreen( );
	}
}

void Framework::addTask( std::string tag, TaskPtr task ) {
	if ( task ) {
		_task_map[ tag ] = task;
	}
}

TaskPtr Framework::getTask( std::string type ) {
	if ( _task_map.find( type ) == _task_map.end( ) ) {
		return TaskPtr( );
	}
	return _task_map[ type ];
}

int Framework::getWindowWidth( ) {
	return _screen_width;
}

int Framework::getWindowHeight( ) {
	return _screen_height;
}
