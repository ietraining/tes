#include <CurieBLE.h>
#define ledPin 13 
#define ledPin2 12
#define ledPin3 11
BLEPeripheral blePeripheral;
unsigned int count=0;

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEUnsignedCharCharacteristic
switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic
switchCharacteristic2("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
BLEUnsignedCharCharacteristic
switchCharacteristic3("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  blePeripheral.setLocalName("LED");
  blePeripheral.setDeviceName("MY DEVICE");

  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);    
  blePeripheral.addAttribute(switchCharacteristic2);
  blePeripheral.addAttribute(switchCharacteristic3);
  switchCharacteristic.setValue(0);
  switchCharacteristic2.setValue(0);
  switchCharacteristic3.setValue(0);
  blePeripheral.begin();
}

void loop() {
  BLECentral central = blePeripheral.central();
  count++;
  delay(1000);
  Serial.println(count);
  if (central) {
    while (central.connected()) {
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value())
          digitalWrite(ledPin, HIGH);
        else
          digitalWrite(ledPin, LOW);
      }
      if (switchCharacteristic2.written()) {
        if (switchCharacteristic2.value()){
          digitalWrite(ledPin2, HIGH);
//          Serial.println("ON");
      }
        else{
            digitalWrite(ledPin2, LOW);
//          Serial.println("OFF");
//          delay(1000);
            }
      }
      if (switchCharacteristic3.written()) {
        if (switchCharacteristic3.value())
          Serial.println("OFF");
        else
          Serial.println("ON");
      }
    }
  }
}

