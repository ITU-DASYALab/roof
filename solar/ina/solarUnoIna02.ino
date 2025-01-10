  #include <TheThingsNetwork.h>
#include <Wire.h>
#include <Adafruit_INA260.h>

Adafruit_INA260 ina260 = Adafruit_INA260(); 

///////////////////// TTN settings ////////////////////////////////////////////////////	
// Set your AppEUI and AppKey
const char *appEui = "70B3D57ED000B95A";
const char *appKey = "59473B61DDCB07F6C72C49D578A81A88";
 
#define loraSerial Serial1
#define debugSerial Serial
 
// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868
 
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
 
void setup()
{

// LoRaWAN, TTN stuff
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  delay(1000);

 //   while (!debugSerial) {
  //  ;
 //   }

 // debugSerial.println("-- STATUS");
 // ttn.showStatus();
  
 // debugSerial.println("-- JOIN");
ttn.join(appEui, appKey);
// EO LoRaWAN, TTN stuff

// Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina260.begin()) {
   // debugSerial.println("Failed to find INA260 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina260.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina260.setCalibration_16V_400mA();

 // debugSerial.println("INA260 ready ...");

}

void loop()
{
 
//debugSerial.println("-- LOOP");

  int busvoltage = 0;
  int loadvoltage = 0;
  int current = 0;
  int power = 0;

  busvoltage = round(ina260.readBusVoltage());
  current = round(ina260.readCurrent());
  power = round(ina260.readPower());
  loadvoltage = busvoltage; // just for now ... as they always say

 
byte payload[8];
payload[0] = highByte(busvoltage);
payload[1] = lowByte(busvoltage);
payload[2] = highByte(loadvoltage);
payload[3] = lowByte(loadvoltage);
payload[4] = highByte(current);
payload[5] = lowByte(current);
payload[6] = highByte(power);
payload[7] = lowByte(power);

// Send it off
ttn.sendBytes(payload, sizeof(payload));
      
delay(120000);

}
