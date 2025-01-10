#include <TheThingsNetwork.h>

// Set your AppEUI and AppKey
const char *appEui = "0000000000000000";
const char *appKey = "00000000000000000000000000000000";
 
#define loraSerial Serial1
#define debugSerial Serial
 
// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868	
 
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
 
void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

    while (!debugSerial) {
    ;
    }

  debugSerial.println("-- STATUS");
  ttn.showStatus();
  
  debugSerial.println("-- JOIN");
ttn.join(appEui, appKey);

}
 
debugSerial.println("-- LOOP");
    
// Prepare array of 1 byte to indicate LED status
byte data[1];
data[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;
    
// Send it off
ttn.sendBytes(data, sizeof(data));
      
delay(10000);





