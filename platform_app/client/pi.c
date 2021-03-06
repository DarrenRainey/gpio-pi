/*
 * =====================================================================================
 *
 *       Filename:  pi.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/28/2013 07:02:48 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */
//gcc led.c -o led -lwiringPi

// led.c
 
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
 
int main (int argc,char* argv[])
{
  if (argc < 2) {
    printf("Usage example: ./led 4 \n");
    return 1;
  }
  int pinNumber = atoi(argv[1]);
 
  if (-1 == wiringPiSetup()) {
    printf("Setup wiringPi failed!");
    return 1;
  }
 
  pinMode(pinNumber, OUTPUT); // set mode to output 
  while(1) {
    digitalWrite(pinNumber, 1); // output a high level 
    delay(800);
    digitalWrite(pinNumber, 0); // output a low level 
    delay(800);
  }
 
  return 0;
}
