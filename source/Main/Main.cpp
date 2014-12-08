#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream> 
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
void ProcessIncomingMessages(Point &p);

void HitWall();
void HitDirt();
void HitRoad();
void HitBanana(); 

std::string MESSAGE_APP_INTERACTION1 = "TODO: Define";
std::string MESSAGE_APP_INTERACTION2 = "TODO: Define";
std::string MESSAGE_SHELL_STARTED = "SHELL";
std::string MESSAGE_SONAR_GATE = "SONAR";

const double START_POINT_X = 50.0; // TODO: Decide this based on where the start is on the actual map
const double START_POINT_Y = 50.0;

const char *ServerName = "192.168.2.100";
const int RecPort = 5001;
const int TransPort = 6000;

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
	std::thread t1(APPListenerThread);
	t1.detach();

	std::thread t2(AppSenderThread);
	t2.detach();

	std::thread t3(MapListenerThread);
	t3.detach();

	// std::thread t4(MapSenderThread,"192.168.2.x");
	// t4.detach();
}

void GetPositionInfo(float &Distance, float &DegreesOffNorth)
{
	// Daryl, please fill this function in
}

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

void ProcessIncomingMessages(Point &p)
{
	while(!MapRecvMessages.empty())
	{
		std::string message = MapRecvMessages.top();
		MapRecvMessages.pop();

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
			//p.x = START_POINT_X; //TODO: Lets test before we start putting in crazy shit like this 
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
  //initializePins();
#endif

  printf ("\nThreads");

  SetUpThreads();

  printf ("\nMap");

  Map map(0, 0, 1);

  map.LoadMap(1, 1);

  std::string MiniMap = "M:" + map.GetAppSizeMap();

  AppSendMessages.push(MiniMap);

  printf("%d", sizeof(MiniMap));

  // DEBUG: not sure if this is needed but needs to be on either Map or App stack
  // SendMessages.push("Test Message");

  // Assume a start point of 0,0 
  p.x = START_POINT_X;
  p.y = START_POINT_Y;
  
  while(true)
  {
	  int NumTiles = 0;
	  Distance = 0;
	  DegreesOffNorth = 0;
	  std::stringstream message;

	  // Pass the point we are at in case we should correct it because we hit a sonar gate 
	  ProcessIncomingMessages(p);

	  GetPositionInfo(Distance, DegreesOffNorth);
	  p2 = map.UpdateLocation(p, Distance, DegreesOffNorth);
	  TileInfo *HitTiles = map.HitTiles(p, p2, NumTiles);

	  for (int i = 0; i < NumTiles; i++)
	  {
		  std::thread t(HandleTile, HitTiles[i]);
		  t.detach();
	  }

	  if ( p2.x + 50 < MAX_TILE_WIDTH)
		  p2.x += 50;
	  else
	  {
		  p2.x = 0;
		  if ( p2.y + 50 < MAX_TILE_HEIGHT )
			  p2.y += 50;
		  else
			  p2.y = 0;
	  }
	  p = p2;
	  
	  // Broadcast the message to the App so Tim can update our location 
	  message << "x:" << p.x << " y:" << p.y;
	  sleep(1);
	  AppSendMessages.push(message.str());
	 
  }

  return 0;
}
