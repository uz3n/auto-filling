#include <EEPROM.h>
#include <TimerOne.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_VL53L0X.h"
#include <NewPing.h>
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define TRIGGER_PIN 7
#define ECHO_PIN 8
#define MAX_DIST 1000
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);
#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int ratus,puluh;
byte puluhan, ratusan;
int toggle = A0;
int tombol = A2;
int toggleJ = A1;
int lamp = 4;
long batas, konter, saving;
int flag, flagS;
int jarak;
float Suhu;
float Dist, Persentase;
void timerIsr() {
 
  if (digitalRead(tombol) == 0 && flag == 0) {
    flag = 10;
  }
  if (flagS == 1) {
    flag = 10;
  }

  if (digitalRead(tombol) == 0 && flag == 1) {
    saving++;
    //Serial.println(saving);
    digitalWrite(lamp, 1);
  } else if (digitalRead(tombol) == 1 && flag == 1) {
    digitalWrite(lamp, 0);
  }

  if (flag == 10 || flag == 11) {
    batas++;
    digitalWrite(lamp, 1);
  }
  if (batas >= konter && flag == 10) {
    digitalWrite(lamp, 0);
    batas = 0;
    flag = 0;
    if (flagS == 1) {
      flagS = 3;
    }
  };
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(toggle, INPUT_PULLUP);
  pinMode(toggleJ, INPUT_PULLUP);
  pinMode(tombol, INPUT_PULLUP);
  pinMode(lamp, OUTPUT);

  puluhan = EEPROM.read(25); //angka 25 dan 26 sebagai lokasi penyimpanan
  ratusan = EEPROM.read(26);
  puluh = puluhan;
  ratus = ratusan;
  konter = ratus * 100;
  konter += puluh;
  Serial.println(konter);
  Wire.begin();
  sensors.begin();
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    //    while (1)
    //      ;
  }

  Timer1.initialize(10000);          // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt(timerIsr);  // attach the service routine here
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus != 4 && flagS == 0) {  // phase failures have incorrect data
    //Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    jarak = measure.RangeMilliMeter;
  }

  if (digitalRead(toggleJ) == 0 && jarak < 180 && flagS == 0) {
    delay(500);
    flagS = 1;
    digitalWrite(lamp, 0);
  }

  if (flagS == 3) {
    delay(2000);
    flagS = 0;
  }



  // put your main code here, to run repeatedly:
  if (digitalRead(toggle) == 0 && flag == 0) {
    flag = 1;
    saving = 0;
    digitalWrite(lamp, 0);
  }

  if (digitalRead(toggle) == 1 && flag == 1) {
    flag = 0;
    digitalWrite(lamp, 0);
    konter = saving;
    puluh = saving % 100;
    ratus = saving / 100;
    puluhan = puluh;
    ratusan = ratus;
    EEPROM.write(25, puluhan);
    EEPROM.write(26, ratusan);
    //Serial.println(konter);
  }



  readSensor(40, 0);
  //readTombol();
  delay(100);
}

void readTombol() {
  Serial.print("tombol: ");
  Serial.print(digitalRead(tombol));
  Serial.print(" toggle: ");
  Serial.print(digitalRead(toggle));
  Serial.print(" toggleJ: ");
  Serial.print(digitalRead(toggleJ));

  Serial.print(" flag: ");
  Serial.print(flag);
  Serial.print(" flags: ");
  Serial.print(flagS);

  Serial.print(" konter: ");
  Serial.println(konter);
}
void readSensor(float DistMin, float DistMax) {
  sensors.requestTemperatures();
  Suhu = sensors.getTempCByIndex(0);
  Dist = sonar.ping_cm();
  if (Dist <= DistMax) {
    Dist == DistMax;
  }
  if (Dist >= DistMin) {
    Dist == DistMin;
  }
  Persentase = map(Dist, DistMin, DistMax, 0, 100); //konvert tinggi ke persentase

  Serial.print("Suhu        =");
  Serial.print(Suhu);
  Serial.print("      ");
  Serial.print("Ketinggian  =");
  Serial.print(Dist);
  Serial.print("      ");
  Serial.print("Persentase air  =");
  Serial.print(Persentase);
  Serial.println("%");
}
