void Main() {
  read_Controler();
  //automatic auto fiing mode
  while (Switch = false) {
    EEPROM.read(setTarget);
    digitalWrite(Relay, LOW);
    read_Controler();
    Detect(byte near, byte far);//near and far for detection container(can)
    while (detect) {
      Detect(byte near, byte far);//near and far for detection container(can)
      GRAM = scale.get_units(), 4;
      while (GRAM != setTarget) {
        digitalWrite(Relay, HIGH);
      }
      digitalWrite(Relay, LOW);
    }

  }
  //setting auto_filling mode
  while (Switch = true) {
    digitalWrite(Relay, LOW);
    read_Controler();
    Detect(byte near, byte far);//near and far for detection container(can)
    while (detect) {
      GRAM = scale.get_units(), 4;
      setTarget = GRAM;
      if (PushButton) {
        digitalWrite(Relay, HIGH);
      } else {
        digitalWrite(Relay, LOW);
      }
    }
  }
  //logic save set target weight at automatic autofilling mode
  if (Switch = false) {
    delay(1500);
    if (Switch = true) {
      delay(500);
    } else {
      delay(3000);
      EEPROM.write(setTarget);
    }
  }
}
