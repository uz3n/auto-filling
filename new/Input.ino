void Detect(byte near, byte far) {
  float range = sensor.readRangeSingleMillimeters();
  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }
  else if (range <= far && range >= near) {
    detect = true;
  } else {
    detect = false;
  }
}
void VolumeLiquid() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distance = duration * SOUND_VELOCITY / 2;

  
}
void Temperature() {
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  Serial.print("Celsius temperature: ");
  Serial.print(temp);// Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  delay(200);
}
void read_Controler(int on, int off) {//read analog from A0 (dfferent from pararel switch and pb)
  int sw = analogRead(A0);
  int pb = sw;
  if (sw == on) {
    Switch = true; PushButton = false;
    if (pb == on ) {
      PushButton = true;
    } else {
      Switch = true; PushButton = false;
    }
  }
  else if(sw == off) {
      Switch = false; PushButton = false;
      if (pb == on ) {
        PushButton = true;
      } else {
        Switch = false; PushButton = false;
      }
    }
  Serial.print("analog    =");
  Serial.print(sw);

}
