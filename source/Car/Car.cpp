#include "Car.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

Car::Car(){
	
}

CarMetrics* Car::getCurrentLocation(){

	return NULL;
}