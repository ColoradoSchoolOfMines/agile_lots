/*
Arduino, HMC5883, magnetometer, XBee code 
 by: Roy Stillwell
 Colorado School of Mines
 created on: 3.30.13
 license: This work is licensed under a Creative Commons Attribution license.
 
 Arduino code example for interfacing with the HMC5883 
 by: Jordan McConnell
 SparkFun Electronics
 created on: 6/30/11
 license: OSHW 1.0, http://freedomdefined.org/OSHW
 
 Analog input 4 I2C SDA
 Analog input 5 I2C SCL
 
 EEPROM code adapted from Tomorrow Lab
 Developer: Ted Ullricis_measuringh <ted@tomorrow-lab.com>
 http://tomorrow-lab.com
 
 */

#include <Wire.h> //I2C Arduino Library
#include <EEPROM.h>
#include <Arduino.h>
#include "EEPROMAnything.h"


#define NOTE_C6  1047
#define NOTE_E6  1319
#define NOTE_G6  1568
#define MEM_SIZE 512 //EEPROM memory size (remaining 2 bytes reserved for count)

#define address 0x1E //0011110b, I2C 7bit address of HMC5883



void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();

  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();


  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
}

void loop(){

  //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
  }
  delay(40);
}









