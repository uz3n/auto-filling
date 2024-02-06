#include "HX711.h"
#include <Wire.h>
#include <VL53L0X.h>
#include <DallasTemperature.h>
#include <EEPROM.h>

#define DOUT  D1   //HX711 DATA
#define CLK  D2    //HX711 CLOCK
const int trigPin = D4;
const int echoPin = D5;
const int Input = A0;
const int Relay = D12;

//uncumment ONE of these for (+speed-accuracy)or(-speed+accuracy)
//#define HIGH_SPEED
#define HIGH_ACCURACY
#define LONG_RANGE      // for high range --accuracy --speed

#define SOUND_VELOCITY 0.034 //define sound velocity in cm/uS
#define ONE_WIRE_BUS D3 //dalas Temp contact with D4 pin

#define EEPROM_ADDRESS 0
HX711 scale(DOUT, CLK);
VL53L0X sensor;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/*VARIABLE*/
float calibration_factor = 98; //98 from calibrating the sensor
int GRAM;
bool detect = false;
long duration;
float distance, temp;
bool Switch = false, PushButton = false;
float setTarget;
void setup() {
  INIT();
  setTarget = EEPROM.read(EEPROM_ADDRESS);
}

void loop() {
  Main (); // the main prorgram for autofilling machine
  
  //  read_Controler(0,0);

  // Weight(); // weight as variable GRAM
  //CalibrationHx711(); //open for calibrating sensor
}
