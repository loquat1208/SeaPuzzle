#include "DxLib.h"
#include "Framework.h"

void main( );
void initialize( );
void finalize( );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Framework::initialize( );
	main( );
	Framework::getInstance( )->run( );
	Framework::finalize( );

	return 0;
}
