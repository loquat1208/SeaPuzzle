#include "File.h"
#include "DxLib.h"
#include "MapMaker.h"
#include <array>
#include <string>
#include "sstream"

File::File( ) {
}

File::~File( ) {
}

void File::save( int stage_num ) {
	FILE *fp;

	std::string         filename;
	std::ostringstream  ost;

	ost.str( "" );
	ost << stage_num;

	filename += "../Data/Map/" + ost.str( ) + ".map";

	errno_t err = fopen_s( &fp, filename.c_str( ), "wb" );
	if ( err != 0 ) {
		return;
	}

	MapMakerPtr map_maker = MapMaker::getTask( );
	std::array< TYPE, Map::MAP_MAX > data = map_maker->getChipType( stage_num );

	fwrite( &data, sizeof( data ), 1, fp );

	fclose( fp );
}

void File::load( int stage_num ) {
	FILE *fh;

	std::string         filename;
	std::ostringstream  ost;
	
	ost.str( "" );
	ost << stage_num;

	filename += "../Data/Map/" + ost.str( ) + ".map";

	errno_t err = fopen_s( &fh, filename.c_str( ), "rb" );
	if ( err != 0 ) {
		return;
	}

	std::array< TYPE, Map::MAP_MAX > data;
	fread( &data, sizeof( data ), 1, fh );

	MapMakerPtr map_maker = MapMaker::getTask( );
	map_maker->setChipType( stage_num, data );

	fclose( fh );
}