
// GPIO stuff
#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_PIN_PATH "/sys/devices/virtual/misc/gpio/pin/"
#define GPIO_FILENAME "gpio"
#define GPIO_OUTPUT_MODE "0"
#define GPIO_INPUT_MODE "1"

#define MAX_MOTOR_VOLTAGE 3.5

// Controller inputs
#define LEFT_MOTOR_INPUT1 "0" // White wire
#define LEFT_MOTOR_INPUT2 "1" // Blue wire
#define RIGHT_MOTOR_INPUT1 "2" // Yellow wire
#define RIGHT_MOTOR_INPUT2 "3" // Red wire

// RC car outputs
#define LEFT_MOTOR_OUTPUT1 "4" // White wire
#define LEFT_MOTOR_OUTPUT2 "5" // Blue wire
#define RIGHT_MOTOR_OUTPUT1 "6" // Yellow wire
#define RIGHT_MOTOR_OUTPUT2 "7" // Red wire

#define LEFT_M1_FD 0
#define LEFT_M2_FD 1
#define RIGHT_M1_FD 2
#define RIGHT_M2_FD 3

#define FORWARD_THROTTLE 1
#define REVERSE_THROTTLE 0

#define POWER "1"
#define GROUND "0"

#define SLOW_THROTTLE ( 255 / 3 )
#define NORMAL_THROTTLE ( ( 2 * 255 ) / 3 )
#define SPEED_THROTTLE 255

struct CarMetrics
{
	float currentDirection;
	float distanceMoved;

};

enum carDirection
{
   MOVE_FORWARD,
   MOVE_REVERSE,
   MOVE_LEFT,
   MOVE_RIGHT,
   MOVE_STOP
};

class Car
{
	public:
		Car();

		CarMetrics* getCurrentLocation();
		void setThrottle(int);
		void onActivateOilSlick();
		void onActivateRedShell();
		void onActivateBananaPeel();
		void onActivateMushroom();
		
	private:
		void* readFromCompass();
		void* readCurrentLinearMovement();

};


bool overrideThrottle();
carDirection readUserInput();
