// Includes from std 
#include <iostream> // io stream 
#include <fstream> // file stream 
#include <sstream> // string stream 
#include <string> // string 

// Includes from project 
#include "Map.h" 


// Function to load map from file 
void Map::LoadMap( int mapNumber, Map map ){



}

// Load map from a file
void Map::LoadMap( int mapNumber ){
		
	std::string mapBaseFilename = "map";
	std::ostringstream mapFilename;
		
	// concatenate mapNumber to mapBaseFilename to get the actual filename 
	mapFilename << mapBaseFilename << mapNumber; 

	// create a file handle for input file stream 
	std::ifstream mapFile;

	// open a file, open only takes char* so have to convert to c string http://www.cplusplus.com/forum/beginner/23266/
	mapFile.open( mapFilename.str().c_str() );

	// test that we successfully opened the file before going any further 
	if ( mapFile.is_open() ){

		// declare a string we will use to represent each line we get via getline 
		std::string line;

		// declare an index we will use for each row of our map 
		int rowIndex = 0; 

		// pull one line from file at a time 
		while ( std::getline( mapFile, line ) ){

			// get size of the line 
			int stringLength = line.size(); 

			// iterate over the line one character at a time and fill in our map
			for ( int columnIndex = 0; columnIndex < stringLength; columnIndex++ ){
				tiles[rowIndex][columnIndex] = Tile(line.at(columnIndex));  //DEBUG -- would be faster to use C-strings if necessary
			}

			rowIndex++;

		}

		mapFile.close();
		
	}

} 

// saves map to a file 
void Map::SaveMap( int mapNumber ){

	std::string mapBaseFilename = "map";
	std::ostringstream mapFilename;
		
	// concatenate mapNumber to mapBaseFilename to get the actual filename 
	mapFilename << mapBaseFilename << mapNumber; 

	// create a file handle for output file stream 
	std::ofstream mapFile;

	// open a file, open only takes char* so have to convert to c string http://www.cplusplus.com/forum/beginner/23266/
	mapFile.open( mapFilename.str().c_str() );

	// test that we successfully opened the file before going any further 
	if ( mapFile.is_open() ){

		// loop for each row of the tiles 
		for (int rowIndex = 0; rowIndex < MAX_TILE_HEIGHT; rowIndex++){

			// declare a string we will use to represent each line we are writing
			std::string line;

			for (int columnIndex = 0; columnIndex < MAX_TILE_WIDTH; columnIndex++){
				line += tiles[rowIndex][columnIndex].GetType(); 
			}

			mapFile << line << "\n"; 

		}

		mapFile.close();
		
	}

}
