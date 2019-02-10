/*
 * A library for the 4 digit display
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Frankie.Chu
 * Create Time: 9 April,2012
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <TimerOne.h>
#include "TM1637.h"
#define ON 1
#define OFF 0

#include "LowPower.h"

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 0;
unsigned char hour = 12;


#define CLK A5//pins definitions for TM1637 and can be changed to other ports
#define DIO A4
TM1637 tm1637(CLK,DIO);

unsigned long counter = 0;

void setup()
{
  Serial.begin(9600);
  tm1637.set(0);
  tm1637.init();
  Timer1.initialize(50000 * 0.6);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
}
void loop()
{
  if(counter % 2 == 0)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  } else {
    tm1637.clearDisplay();
  }
  //LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF,
                TIMER1_ON, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);

}
void TimingISR()
{
  //Serial.println("Interrupt");
  counter ++;
}
void TimeUpdate(void)
{
  int small_counter = counter / 50;
  TimeDisp[3] = small_counter % 10;
  TimeDisp[2] = (small_counter / 10) % 10;
  TimeDisp[1] = (small_counter / 100) % 10;
  TimeDisp[0] = (small_counter / 1000) % 10;
}
