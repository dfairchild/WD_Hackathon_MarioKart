#include "Car.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

int fd[4];

Car::Car(){
	char path[100];
	
   // Init input GPIO pins
	memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_INPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, LEFT_MOTOR_INPUT1);
   system(path);

   memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_INPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, LEFT_MOTOR_INPUT2);
   system(path);

   memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_INPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, RIGHT_MOTOR_INPUT1);
   system(path);

   memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_INPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, RIGHT_MOTOR_INPUT2);
   system(path);

   // Init output GPIO pins
   memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_OUTPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT1);
   system(path);

   memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_OUTPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT2);
   system(path);

   memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_OUTPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT1);
   system(path);

   memset(path, 0, sizeof(path));
   sprintf(path, "echo %s > %s%s%s", GPIO_OUTPUT_MODE, GPIO_MODE_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT2);
   system(path);

   // Open the files for the inputs
   memset(path, 0, sizeof(path));
   sprintf(path, "%s%s%s", GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_INPUT1);
   fd[LEFT_M1_FD] = open(path, O_RDONLY);

   memset(path, 0, sizeof(path));
   sprintf(path, "%s%s%s", GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_INPUT2);
   fd[LEFT_M2_FD] = open(path, O_RDONLY);

   memset(path, 0, sizeof(path));
   sprintf(path, "%s%s%s", GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_INPUT1);
   fd[RIGHT_M1_FD] = open(path, O_RDONLY);

   memset(path, 0, sizeof(path));
   sprintf(path, "%s%s%s", GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_INPUT1);
   fd[RIGHT_M2_FD] = open(path, O_RDONLY);

}

CarMetrics* Car::getCurrentLocation() {

	return NULL;
}

void Car::setThrottle(int throttle) {
   char path[100];
   int leftMotor, rightMotor;
   carDirection userDirection;

   if ( overrideThrottle() ) {

   } else {

      userDirection = readUserInput();

      // Initialize system command
      memset(path, 0, sizeof(path));

      // Set the percentage of acceleration for each motor:
      switch ( userDirection )
      {

         case MOVE_FORWARD :

            leftMotor = FORWARD_THROTTLE;
            rightMotor = FORWARD_THROTTLE;
            break;

         case MOVE_REVERSE :

            leftMotor = REVERSE_THROTTLE;
            rightMotor = REVERSE_THROTTLE;
            break;

         case MOVE_LEFT :

            leftMotor = REVERSE_THROTTLE;
            rightMotor = FORWARD_THROTTLE;
            break;

         case MOVE_RIGHT :

            leftMotor = FORWARD_THROTTLE;
            rightMotor = REVERSE_THROTTLE;
            break;

         case MOVE_STOP :

            leftMotor = 0;
            rightMotor = 0;
            break;

         default :
            break;

      }

      // Configure the left motor:
      switch ( leftMotor )
      {

         case FORWARD_THROTTLE :

            // Set the left motor to go forwards
            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", POWER, GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT1);
            system(path);

            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", GROUND, GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT2);
            system(path);

            break;

         case REVERSE_THROTTLE :

            // Set the left motor to go backwards
            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", GROUND, GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT1);
            system(path);

            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", POWER, GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT2);
            system(path);

            break;

         default :

            // Turn off the left motor
            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", GROUND, GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT1);
            system(path);

            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", GROUND, GPIO_PIN_PATH, GPIO_FILENAME, LEFT_MOTOR_OUTPUT2);
            system(path);

            break;

      }

      // Configure the right motor:
      switch ( rightMotor )
      {

         case FORWARD_THROTTLE :

            // Set the right motor to go forwards
            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", POWER, GPIO_PIN_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT1);
            system(path);

            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", GROUND, GPIO_PIN_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT2);
            system(path);

            break;

         case REVERSE_THROTTLE :

            // Set the right motor to go backwards
            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", GROUND, GPIO_PIN_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT1);
            system(path);

            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", POWER, GPIO_PIN_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT2);
            system(path);

            break;

         default :

            // Turn off the right motor
            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", POWER, GPIO_PIN_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT1);
            system(path);

            memset(path, 0, sizeof(path));
            sprintf(path, "echo %s > %s%s%s", GROUND, GPIO_PIN_PATH, GPIO_FILENAME, RIGHT_MOTOR_OUTPUT2);
            system(path);

            break;

      }

   }

}

// This function handles whether the user should not be able to control the car
bool overrideThrottle(){
   return false;
}

// This function reads the current user RC input
carDirection readUserInput(){
   char pinEnabled[2];
   bool leftMotor1, leftMotor2, rightMotor1, rightMotor2;
   int compare;

   // Read from the left motor input1
   memset(pinEnabled, 0, sizeof(pinEnabled));
   read(fd[LEFT_M1_FD], pinEnabled, sizeof(pinEnabled));
   compare = strcmp(pinEnabled, POWER);
   leftMotor1 = ( compare == 0 );

   // Read from the left motor input2
   memset(pinEnabled, 0, sizeof(pinEnabled));
   read(fd[LEFT_M2_FD], pinEnabled, sizeof(pinEnabled));
   compare = strcmp(pinEnabled, POWER);
   leftMotor2 = ( compare == 0 );

   // Read from the right motor input1
   memset(pinEnabled, 0, sizeof(pinEnabled));
   read(fd[RIGHT_M1_FD], pinEnabled, sizeof(pinEnabled));
   compare = strcmp(pinEnabled, POWER);
   rightMotor1 = ( compare == 0 );

   // Read from the right motor input2
   memset(pinEnabled, 0, sizeof(pinEnabled));
   read(fd[RIGHT_M2_FD], pinEnabled, sizeof(pinEnabled));
   compare = strcmp(pinEnabled, POWER);
   rightMotor2 = ( compare == 0 );

   // If the left motor is moving forward:
   if ( leftMotor1 && !leftMotor2 ) {

      // Either the car should be going forward or to the right:
      if ( rightMotor1 && !rightMotor2 ) {
         return MOVE_FORWARD;
      } else {
         return MOVE_RIGHT;
      }

   // Otherwise, if the left motor is going in reverse:
   } else if ( leftMotor2 && !leftMotor1 ) {

      // Either the car should be going in reverse or to the left:
      if ( rightMotor2 && !rightMotor1 ) {
         return MOVE_REVERSE;
      } else {
         return MOVE_LEFT;
      }

   // Otherwise, the car should not be moving:
   } else {

      return MOVE_STOP;

   }

}
