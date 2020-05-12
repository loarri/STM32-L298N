/*----------------------------------------
/*
/* STM32-F411RE + L298N + potentiometer
/*
/* Author: Lorenzo Arrigoni
/*
/* Date: May 2020
/*
/*-----------------------------------------*/


#include "mbed.h"
/*
#define ENA 8
#define ENB 13

#define black 9  // In1
#define brown 10  // In2
#define orange 11  // In3
#define yellow 12  // In4
*/
//L298n connections
DigitalOut pinI1(D5);
DigitalOut pinI2(D6);
DigitalOut pinI3(D10);
DigitalOut pinI4(D11);
DigitalOut ENA(D12);    //Left
DigitalOut ENB(D13);    //Right
AnalogIn analog_value(A2);

DigitalIn mybutton(USER_BUTTON);

void forward(int i, float j);
void reverse(int i, float j);
//long map(long x, long in_min, long in_max, long out_min, long out_max);
float map(float in, float inMin, float inMax, float outMin, float outMax);

int main()
{
    float meas;
    while (true) 
    {
        meas = analog_value.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
        printf("\r\nvalore letto = %f\n", meas);
        meas = map(meas, 0, 1023, 0, 10);
        //meas = meas * 0.01; // Change the value to be in the 0 to 3300 range
        printf("\r\nmeasure = %f\n", meas);
        if (mybutton == 0) { // Button is pressed
          forward(100, meas);
        } else {
          reverse(100, meas);   
        };
        /*wait(1.0f);
        reverse(100, 0.1f);
        wait(1.0f);
        */
    }
}

/*
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
*/
float map(float in, float inMin, float inMax, float outMin, float outMax) {
  // check it's within the range
  if (inMin<inMax) { 
    if (in <= inMin) 
      return outMin;
    if (in >= inMax)
      return outMax;
  } else {  // cope with input range being backwards.
    if (in >= inMin) 
      return outMin;
    if (in <= inMax)
      return outMax;
  }
  // calculate how far into the range we are
  float scale = (in-inMin)/(inMax-inMin);
  // calculate the output.
  return outMin + scale*(outMax-outMin);
}

void reverse(int i, float j) 
{

    // Pin 8 Enable A Pin 13 Enable B on
    //digitalWrite(ENA, HIGH);
    ENA = 1;
    //digitalWrite(ENB, HIGH);
    ENB = 1;
    
    //j = j + .010f;
    while (1)   {
    
    //digitalWrite(black, 0);
    //digitalWrite(brown, 1);
    //digitalWrite(orange, 1);
    //digitalWrite(yellow, 0);
    pinI1 = 0;
    pinI2 = 1;
    pinI3 = 1;
    pinI4 = 0;
    
    wait(j);  
    i--;
    if (i < 1) break;
    
    /*
    digitalWrite(black, 0);
    digitalWrite(brown, 1);
    digitalWrite(orange, 0);
    digitalWrite(yellow, 1);
    */
    pinI1 = 0;
    pinI2 = 1;
    pinI3 = 0;
    pinI4 = 1;
    wait(j);
    i--;
    if (i < 1) break;
    
    /*
    digitalWrite(black, 1);
    digitalWrite(brown, 0);
    digitalWrite(orange, 0);
    digitalWrite(yellow, 1);
    */
    pinI1 = 1;
    pinI2 = 0;
    pinI3 = 0;
    pinI4 = 1;
    wait(j);  
    i--;
    if (i < 1) break;
    /*
    digitalWrite(black, 1);
    digitalWrite(brown, 0);
    digitalWrite(orange, 1);
    digitalWrite(yellow, 0);
    */
    pinI1 = 1;
    pinI2 = 0;
    pinI3 = 1;
    pinI4 = 0;
    wait(j);
    i--;
    if (i < 1) break;
    }
    
    // all outputs to stepper off
    //digitalWrite(ENA, LOW);
    //digitalWrite(ENB, LOW);
    ENA = 0;
    ENB = 0;
}



void forward(int i, float j) 
{

    // Pin 8 Enable A Pin 13 Enable B on
    //digitalWrite(ENA, HIGH);
    //digitalWrite(ENB, HIGH);
    ENA = 1;
    ENB = 1;
    
    //j = j + .010f;
    while (1)   {
    /*
    digitalWrite(black, 1);
    digitalWrite(brown, 0);
    digitalWrite(orange, 1);
    digitalWrite(yellow, 0);
    */
    pinI1 = 1;
    pinI2 = 0;
    pinI3 = 1;
    pinI4 = 0;
    wait(j);
    i--;
    if (i < 1) break; 
    
    
    /*
    digitalWrite(black, 1);
    digitalWrite(brown, 0);
    digitalWrite(orange, 0);
    digitalWrite(yellow, 1);
    */
    pinI1 = 1;
    pinI2 = 0;
    pinI3 = 0;
    pinI4 = 1;
    wait(j);  
    i--;
    if (i < 1) break;
    /*
    digitalWrite(black, 0);
    digitalWrite(brown, 1);
    digitalWrite(orange, 0);
    digitalWrite(yellow, 1);
    */
    pinI1 = 0;
    pinI2 = 1;
    pinI3 = 0;
    pinI4 = 1;
    wait(j);
    i--;
    if (i < 1) break;
    /*
    digitalWrite(black, 0);
    digitalWrite(brown, 1);
    digitalWrite(orange, 1);
    digitalWrite(yellow, 0);
    */
    pinI1 = 0;
    pinI2 = 1;
    pinI3 = 1;
    pinI4 = 0;
    wait(j);  
    i--;
    if (i < 1) break;
    
    
    }
    
    // all outputs to stepper off
    //digitalWrite(ENA, LOW);
    //digitalWrite(ENB, LOW);
    ENA = 0;
    ENB = 0;
}
