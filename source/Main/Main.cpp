#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <thread>
#include "..\..\source\Map\Map.h"
#include "..\..\source\Car\Car.h"
#include "..\..\source\Networking\sock.h"

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif


//stuff for initializing pins
#define PIN_HIGH 1
#define PIN_LOW 0
#define PIN_OUTPUT 1
#define PIN_INPUT 0
#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_PIN_PATH "/sys/devices/virtual/misc/gpio/pin/"
#define GPIO_FILENAME "gpio"

void setPinMode(int pinID, int mode);
void writeFile(int fileID, int value);
void HandleTile(TileInfo tile);
void GetPositionInfo(float &Distance, float &DegreesOffNorth);
void ProcessIncomingMessages();

void HitWall();
void HitDirt();
void HitRoad();
void HitBanana(); 

std::string MESSAGE_APP_INTERACTION1 = "TODO: Define";
std::string MESSAGE_APP_INTERACTION2 = "TODO: Define";
std:string MESSAGE_SHELL_STARTED = "SHELL";
std:string MESSAGE_SONAR_GATE = "SONAR";

//setups up pins 2 and 4 as input pins to read compass/speed
void initializePins(){

	//setup pin mode for pin 2 as input ** THIS IS HARD CODED, BAD!
	char path[256];
	memset(path,0,sizeof(path));
	sprintf(path, "%s%s%d", GPIO_MODE_PATH, GPIO_FILENAME, 2);
	int pinModeForPin2 = open(path, std::ios::in);

	setPinMode(pinModeForPin2, PIN_INPUT);

	//setup pin mode for pin 4 as input ** THIS IS HARD CODED BAD!    
	memset(path,0,sizeof(path));
	sprintf(path, "%s%s%d", GPIO_MODE_PATH, GPIO_FILENAME, 4);
	int pinModeForPin4 = open(path, std::ios::in);

	setPinMode(pinModeForPin4, PIN_INPUT);

}

void writeFile(int fileID, int value)
{
	char buffer[4];  
	memset((void *)buffer, 0, sizeof(buffer)); 
	sprintf(buffer, "%c", value);
	lseek(fileID, 0, SEEK_SET);   
	write(fileID, buffer, sizeof(buffer));
}

void setPinMode(int pinID, int mode)
{
  writeFile(pinID, mode);
}

void SetUpThreads()
{
	std::thread t1(ListenerThread, 5000);
	t1.detach();

	std::thread t2(SenderThread, 5001, 5002, "192.168.1.6");
	t2.detach();
}

void GetPositionInfo(float &Distance, float &DegreesOffNorth)
{

}

// These functions should be threads 
// OR they will just affect some GPIO so it doesn't matter that they aren't threads 
void HitDirt()
{
	// Call that handles affecting the car when it hits dirt 
}

void HitWall()
{
	// Call that handles affecting the car when it hits the wall 
}

void HitRoad()
{
	// Call that handles affecting the car when it hits the road 
}

void HitBanana()
{
	// Call that handles affecting the car when it hits a banana 
}

void HandleTile(TileInfo tile)
{
	char tileType;
	tileType = tile.tile.type; 
	
	switch( tileType )
	{
		case DIRT: 
			HitDirt();
			break;
		case ROAD:
			HitRoad();
			break;
		case BANANA:
			HitBanana();
			break;
		case WALL:
			HitWall();
			break;
		case START1:
			// Push a passing finish line message
			HitRoad();
			break;
		case START2:
			// Push a passing finish line message 
			HitRoad(); 
			break; 
		default:
			HitRoad();
			break; 
	}
}

void ProcessIncomingMessages()
{
	while(!RecvMessages.empty())
	{
		std::string message = RecvMessages.top();
		RecvMessages.pop();

		if( message.compare( MESSAGE_APP_INTERACTION1 ) ) 
		{
			// Handle app interaction (undefined)
		}
		else if( message.compare( MESSAGE_APP_INTERACTION2 ) ) 
		{
			// Handle app interaction (undefined) 
		}
		else if( message.compare( MESSAGE_SHELL_STARTED ) ) 
		{
			// Handle shell started (register it with map and start timer)
		}
		else if( message.compare( MESSAGE_SONAR_GATE ) )
		{
			// Handle passing through sonar gate 
		}
		// Throw away unrecognized messages 
	}
}

int main(void) 
{
	float Distance, DegreesOffNorth;
	Point p, p2;

// Skip pin inialization on Visual Studio to allow for compliation tests
#if _MSC_VER

#else
  initializePins();
#endif

  SetUpThreads();

  Map map(0, 0, 1);

  map.LoadMap(1, 1);

  SendMessages.push("Test Message");

  while(true)
  {
	  int NumTiles = 0;

	  ProcessIncomingMessages();

	  GetPositionInfo(Distance, DegreesOffNorth);
	  p2 = map.UpdateLocation(p, Distance, DegreesOffNorth);
	  TileInfo *HitTiles = map.HitTiles(p, p2, NumTiles);

	  for (int i = 0; i < NumTiles; i++)
	  {
		  std::thread t(HandleTile, HitTiles[i]);
		  t.detach();
	  }

	  p = p2;
  }

  return 0;
}
