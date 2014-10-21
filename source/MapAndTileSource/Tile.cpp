
class Tile {

	// Tile is a class to hold tile data info 
	// Map is comprised of a 1000x1000 of tiles 
	// Each tile will equate to 0.25"
	// Max map size is therefore a ~20.8' per side

private: 
	char type;
    char defaultType; 

public: 
	char GetType(){
		return type;
	}
	void SetType(int newType){
		type = newType;
	}
	void SetDefaultType(int newDefaultType){
		defaultType = newDefaultType;
	}
	void ResetToDefault(){
		type = defaultType; 
	}
}
