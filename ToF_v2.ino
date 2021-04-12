/*
  Reading distance from the laser based VL53L1X
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SparkFun labored with love to create this code. Feel like supporting open source hardware? 
  Buy a board from SparkFun! https://www.sparkfun.com/products/14667

  This example prints the distance to an object.

  Are you getting weird readings? Be sure the vacuum tape has been removed from the sensor.
*/
#include <MIDI.h>
#include <Wire.h>
#include "SparkFun_VL53L1X.h"
#include "Variables.h"

//Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 33
#define INTERRUPT_PIN 13
int lastDistance;

//SFEVL53L1X distanceSensor;
//Uncomment the following line to use the optional shutdown and interrupt pins.
SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

void setup(void)
{
  Wire.begin();
  Wire.setSDA(18);
  Wire.setSCL(19);
  //Serial.begin(115200);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
  Serial.println("VL53L1X Qwiic Test");

  if (distanceSensor.begin() == true)
    Serial.println("Sensor online!");
  
  
  distanceSensor.setDistanceModeShort();  
  distanceSensor.setIntermeasurementPeriod(40);
  Serial.println(distanceSensor.getIntermeasurementPeriod());
}

void loop(void)
{
  //usbMIDI.read();
  distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
  int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.stopRanging();

  
  int difference = distance - lastDistance;

  if (abs(difference) >= 5)
  {
    Serial.print("A significant change has been detected: ");
    Serial.print(distance);
    Serial.println();
    doMidiStuff(distance);

    
    Serial.print("Distance(mm): ");
    Serial.print(distance);
    Serial.println();
  }
  lastDistance = distance;
}


void myNoteOn(byte channel, byte note, byte velocity)
{
  // When using MIDIx4 or MIDIx16, usbMIDI.getCable() can be used
  // to read which of the virtual MIDI cables received this message.
  Serial.print("Note On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);

//   if (channel == 10) // If channel 10 move root
//  {
//  float noteVal = 0;
//  noteVal = (float)note;
//  root = (int)noteVal;
//  mtof(noteVal);
//  }
//
//  if (channel == 11) // If channel 10 move scale
//  {
//    int noteVal2 = 0;
//    noteVal2 = (int)note % 12;
//   // Serial.print("Note Value mod: ");
//   // Serial.println(noteVal2); // should wrap around 12 values
//    if (noteVal2 < amountOfScales-1)
//    {
//      scalePusher = noteVal2;
//    }
//  }
  
}

void doMidiStuff (int distance)
{
  usbMIDI.sendNoteOff(lastMid, 0, 1);    // Send a Note (pitch 42, velo 127 on channel 1)

  int distanceNormal = (int)distance / 16;
  
  int selecta = distanceNormal % 8; // of the values just wrap round 8

  int octava = (distanceNormal / 8) * 12;

  int mid;

  mid = root + octava + noteArray[3][selecta];

  Serial.print("Midi Note val: ");
  Serial.println(mid);

  if (mid != lastMid)
  {
    usbMIDI.sendNoteOn(mid, 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
    
  }
   lastMid = mid; 

  //delay(50);
  //usbMIDI.sendNoteOff(mid, 0, 1);    // Send a Note (pitch 42, velo 127 on channel 1)

//  unsigned long currentMillis = millis();
// 
//  if(currentMillis - previousMillis > interval) 
//  {
//    // save the last time you blinked the LED 
//    previousMillis = currentMillis;   
//    usbMIDI.sendNoteOff(lastMid, 0, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
//
//  }
}

void mtof(float midiNote)
{
  midiFreq = (powf(2, (midiNote - 69)/12) * basePitch) / 8; // Dots in equations mean multiply
  //Serial.print("Midi 2 freq conversion is: ");
}

void myNoteOff(byte channel, byte note, byte velocity)
{
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
}
