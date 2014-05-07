/*
Copyright 2013 Institute IRNAS Race - Luka Mustafa - Musti, musti@irnas.eu

ServalRuggedBatteryPack is to be used with Energia environment and MSP430G2452

The ServalRuggedBatteryPack is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

The ServalRuggedBatteryPack library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with the SFPddm library. If not, see http://www.gnu.org/licenses/.

*/

#include <Wire.h>
//The library needs to be modified if it does not fit the MCU by removing functions containing float. Calibration constant in the library needs to be modified.
#include <Adafruit_INA219.h>

//Pinout
#define IN_A_INPUT12 A0
//divider 1M/56k, max value with 2.5Vref = 47.123V
#define IN_A_INPUT5 A3
//divider 1M/470k, max value with 2.5Vref = 7.812V
#define IN_A_OUTPUT A4
//divider 1M/180k, max value with 2.5Vref = 16.389V
#define IN_A_INTERNAL 11

#define OUT_CONTROL P1_5
#define OUT_LED P2_7

#define VOLTAGE_LOW 2700
#define VOLTAGE_HIGH 3000

boolean LOAD_CTRL=LOW;

int battery_voltage=0;

Adafruit_INA219 ina219;

void setup()
{  
  Serial.begin(9600);
  
  pinMode(IN_A_INPUT12,INPUT);
  pinMode(IN_A_INPUT5,INPUT);
  pinMode(IN_A_OUTPUT,INPUT);
  pinMode(OUT_CONTROL,OUTPUT);
  digitalWrite(OUT_CONTROL,HIGH);
  pinMode(OUT_LED,OUTPUT);
  digitalWrite(OUT_LED,HIGH);
  analogReference(INTERNAL2V5);
  
  ina219.begin();
  //modify I2C to be non-blocking
  
}

int GETfunctions[5]={(int)nodewatcher};
int SETfunctions[1]={(int)testSET};

//***************************************************************
// Functions for reading/writing and sensor communication

//**************************

void nodewatcher(){
  Serial.println("#START");
  
  int16_t shuntvoltage = 0;//ina219.getShuntVoltage_raw();
  int16_t busvoltage = 0;//ina219.getBusVoltage_raw();
  int16_t current_mA = 0;//ina219.getCurrent_raw();  
  
  if(LOAD_CTRL){
    shuntvoltage = ina219.getShuntVoltage_raw()/100;
    busvoltage = ina219.getBusVoltage_raw();
    current_mA = ina219.getCurrent_raw()/3;
  }
  
  battery_voltage = map(analogRead(IN_A_INTERNAL),0,1023,0,5000);
  int input12_voltage = map(analogRead(IN_A_INPUT12),0,1023,0,47123);
  int input5_voltage = map(analogRead(IN_A_INPUT5),0,1023,0,7812);
  int output_voltage = map(analogRead(IN_A_OUTPUT),0,1023,0,16389);
  
  Serial.print("environment.sensor0.temp:");
  Serial.println(battery_voltage,DEC);
  Serial.println("environment.sensor0.serial: Battery (mV)");
  
  Serial.print("environment.sensor1.temp:");
  Serial.println(input12_voltage,DEC);
  Serial.println("environment.sensor1.serial: HV input (mV)");
  
  Serial.print("environment.sensor2.temp:");
  Serial.println(input5_voltage,DEC);
  Serial.println("environment.sensor2.serial: USB input (mV)");
  
  Serial.print("environment.sensor3.temp:");
  Serial.println(output_voltage,DEC);
  Serial.println("environment.sensor3.serial: Output (mV)");
  
  Serial.print("environment.sensor4.temp:");
  Serial.println(shuntvoltage,DEC);
  Serial.println("environment.sensor4.serial: Shunt voltage (mV)");
  
  Serial.print("environment.sensor5.temp:");
  Serial.println(busvoltage,DEC);
  Serial.println("environment.sensor5.serial: Bus voltage (mV)");
  
  Serial.print("environment.sensor6.temp:");
  Serial.println(current_mA,DEC);
  Serial.println("environment.sensor6.serial: Current (mA)");
  

  Serial.println("#STOP");
}

void testSET(int data){
  Serial.println("#START");
  Serial.println("Test");
  Serial.println("#STOP");
}


void loop()
{
  //battery protection
  battery_voltage = map(analogRead(IN_A_INTERNAL),0,1023,0,5000);
  if (battery_voltage<VOLTAGE_LOW && LOAD_CTRL==HIGH){
    LOAD_CTRL=LOW;
  }
  if (battery_voltage>VOLTAGE_HIGH && LOAD_CTRL==LOW){
    LOAD_CTRL=HIGH;
  }
  digitalWrite(OUT_CONTROL,LOAD_CTRL);  
  
  // handles incoming UART commands
  // wait for at least 7 characters:
  while (Serial.available() > 3) {
    int x = 0;
    int v = 0;
    // Check for "ACOM /" string
    if(Serial.find("A ")){
      // parse command number after /
      x = Serial.parseInt(); 
      //if termianted, call GET
      if (Serial.read() == '\n'){
        // call GET function
        ((void (*)()) GETfunctions[x])();
      }
      //if nto terminated, read value argument and call SET
      else{
        v = Serial.parseInt();
        ((void (*)(int)) SETfunctions[x])(v); 
      }
      //more arguments can be supported in the same manner
    }
  }
}
