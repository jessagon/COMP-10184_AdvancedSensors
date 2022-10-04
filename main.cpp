/*
"StAuth10184: I Jesse Em, 000295218 certify that this material is my original work. 
No other person's work has been used without due acknowledgement. 
I have not made my work available to anyone else."
*/
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
 
//global temperature
float fTemp; 

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {   //array of bytes
  for (uint8_t i = 0; i < 8; i++) {               
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
// formatting
  Serial.println("");
}

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  // variable for the address, array of bytes
  DeviceAddress addy;

  //will return 1 if the sensor is connected
  String str = String(DS18B20.getAddress(addy, oneWireBus));

  if (str == "1") {
    // print the address and check for the sensor
    Serial.print("\nTemperature application \nFound DS18B20 sensor, Address: ");
    printAddress(addy);
  }
  
} 
 
void loop() { 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 

  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 

  // output the correct string depending on the weather
  String weather = "";

  //if the sensor is not connected
  if (fTemp == (-127)) {
    Serial.println("No sensor connected. Terminating program.");

    //sleep my child, for 49 days
    delay(4294967295); 
  }
    else if (fTemp < 10) {
    weather = "Cold!";
  } else if (fTemp > 10 && fTemp <= 15) {
    weather = "Cool";
  } else if (fTemp > 15 && fTemp <= 25) {
    weather = "Perfect";
  } else if (fTemp > 25 && fTemp <= 30) {
    weather = "Warm";
  } else if (fTemp > 30 && fTemp <= 35) {
    weather = "Hot";
  } else if (fTemp > 35) {
    weather = "Too Hot!";
  } 

  // print the temp to the USB serial monitor 
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + weather); 

  // wait 5s
  delay(5000); 
} 