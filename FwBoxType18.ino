//
// Copyright (c) 2020 Fw-Box (https://fw-box.com)
// Author: Hartman Hsieh
//
// Description :
//   None
//
// Connections :
//
// Required Library :
//

#include "FwBox.h"


#define DEVICE_TYPE 18
#define FIRMWARE_VERSION "1.1.2"

#define PIN_LED 22 // TTGO T7 Mini32
//#define PIN_LED 2 // AI-Thinker NodeMCU-32S

//
// Global variable
//

void setup()
{
  Serial.begin(9600);

  //
  // Blink the LED when updating firmware.
  //
  FwBoxIns.setGpioStatusLed(PIN_LED); // TTGO T7 Mini32

  //
  // Initialize the fw-box core (early stage)
  //
  fbEarlyBegin(DEVICE_TYPE, FIRMWARE_VERSION);

  //
  // Initialize the fw-box core
  //
  fbBegin(DEVICE_TYPE, FIRMWARE_VERSION);

  //
  // Setup MQTT subscribe callback
  //
  setRcvValueCallback(onReceiveValue);

  //WiFi.disconnect(); // HTM_DEBUG
  //Serial.println("==========18==========");
} // void setup()

void loop()
{

  FwBoxIns.setValue(0, digitalRead(PIN_LED)); // 0 means the first value (val0)

  //
  // Run the handle
  //
  fbHandle();

  //digitalWrite(PIN_LED, LOW);

} // END OF "void loop()"

void onReceiveValue(int valueIndex, String* payload)
{
  Serial.print("onReceiveValue valueIndex = ");
  Serial.println(valueIndex);
  Serial.print("onReceiveValue *payload = ");
  Serial.println(*payload);

  if(valueIndex == 0) { // 0 means the first value (val0)
    payload->toUpperCase();
    if(payload->equals("ON") == true)
    {
      digitalWrite(PIN_LED, HIGH);
    }
    else
    {
      digitalWrite(PIN_LED, LOW);
    }
  }
}
