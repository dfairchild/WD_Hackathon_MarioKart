#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//stuff for initializing pins
#define PIN_HIGH 1
#define PIN_LOW 0
#define PIN_OUTPUT 1
#define PIN_INPUT 0
#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_PIN_PATH "/sys/devices/virtual/misc/gpio/pin/"
#define GPIO_FILENAME "gpio"

//setups up pins 2 and 4 as input pins to read compass/speed
void initializePins(){

	//setup pin mode for pin 2 as input ** THIS IS HARD CODED, BAD!
	char path[256];
	memset(path,0,sizeof(path));
	sprintf(path, "%s%s%d", GPIO_MODE_PATH, GPIO_FILENAME, 2);
	int pinModeForPin2 = open(path, ios::in);

	setPinMode(pinModeForPin2, PIN_INPUT);

	//setup pin mode for pin 4 as input ** THIS IS HARD CODED BAD!    
	memset(path,0,sizeof(path));
	sprintf(path, "%s%s%d", GPIO_MODE_PATH, GPIO_FILENAME, 4);
	int pinModeForPin4 = open(path, ios::in);

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

int main(void) 
  printf("Hello, world!\n"); 

  initializePins();

  return 0;
}
