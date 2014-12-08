#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  /*Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);*/
}

void setup(void) 
{
  Serial.begin(9600);
  //Serial.println("Accelerometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!accel.begin() || !mag.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    printf("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  } 
  
  /* Display some basic information on this sensor */
  //displaySensorDetails();
}

void loop(void) 
{
  char buff[10];
  FILE *fp = popen("ls","r");
  while(fgets(buff,10,fp)!=NULL) {
    printf("LS->%s", buff);
  }
  pclose(fp);

  float text;

  /* Get a new sensor event */ 
  sensors_event_t eventAcc; 
  accel.getEvent(&eventAcc);
  sensors_event_t eventMag;
  mag.getEvent(&eventMag);
  
  float Pi = 3.14159;
  // Calculate the angle of the vector y,x
  float heading = (atan2(eventMag.magnetic.y,eventMag.magnetic.x) * 180) / Pi;
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  
  
  /* Display the mag results (in Deg off north) */
  printf("%f", heading);
  printf("\n");
  scanf("%f",&text);
  printf("I read from console: %f", text);
   /* Display the acc results (acceleration is measured in m/s^2) */
  printf("X accel in m per second: %f", eventAcc.acceleration.x);
  printf("\n");
  printf("Y accel in m per second: %f", eventAcc.acceleration.y);
  printf("\n");
  
  delayMicroseconds(1000000);  

}
