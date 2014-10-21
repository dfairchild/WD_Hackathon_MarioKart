// Includes from std 
#include <iostream> // io stream 
#include <fstream> // file stream 
#include <sstream> // string stream 
#include <string> // string 

// Includes from project 
#include "Tile.h" 

using namespace std; 

const int MAP_ROWS = 1000; 
const int MAP_COLUMNS = 1000; 


// Function to load map from file 
void LoadMap( int mapNumber, Map map ){



}

class Map{

	Tile tileArray[MAP_ROWS][MAP_COLUMNS]; 

	// Load map from a file
	void LoadMap( int mapNumber ){
		
		string mapBaseFilename = "map";
		ostringstream mapFilename;
		
		// concatenate mapNumber to mapBaseFilename to get the actual filename 
		mapFilename << mapBaseFilename << mapNumber; 

		// create a file handle for input file stream 
		ifstream mapFile;

		// open a file, open only takes char* so have to convert to c string http://www.cplusplus.com/forum/beginner/23266/
		mapFile.open( mapFilename.str().c_str() );

		// test that we successfully opened the file before going any further 
		if ( mapFile.is_open() ){

			// declare a string we will use to represent each line we get via getline 
			string line;

			// declare an index we will use for each row of our map 
			int rowIndex; 

			// pull one line from file at a time 
			while ( getline( mapFile, line ) ){

				// get size of the line 
				int stringLength = line.size(); 

				// iterate over the line one character at a time and fill in our map
				for ( int columnIndex = 0; columnIndex < stringLength; columnIndex++ ){
					tileArray[rowIndex][columnIndex] = line.at(columnIndex);  //DEBUG -- would be faster to use C-strings if necessary
				}

			}

			mapFile.close();
		
		}

	} 

	// saves map to a file 
	void SaveMap( int mapNumber ){

		string mapBaseFilename = "map";
		ostringstream mapFilename;
		
		// concatenate mapNumber to mapBaseFilename to get the actual filename 
		mapFilename << mapBaseFilename << mapNumber; 

		// create a file handle for output file stream 
		ofstream mapFile;

		// open a file, open only takes char* so have to convert to c string http://www.cplusplus.com/forum/beginner/23266/
		mapFile.open( mapFilename.str().c_str() );

		// test that we successfully opened the file before going any further 
		if ( mapFile.is_open() ){

			// loop for each row of the tileArray 
			for ( int rowIndex = 0; rowIndex < MAP_ROWS; rowIndex++ ){

				// declare a string we will use to represent each line we are writing
				string line;

				for ( int columnIndex = 0; columnIndex < MAP_COLUMNS; columnIndex++ ){
					line.append( tileArray[rowIndex][columnIndex].GetType() ); 
				}

				mapFile << line << "\n"; 

			}

			mapFile.close();
		
		}

	}

}