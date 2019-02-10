#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LowPower.h>
#include <TimerOne.h>
//#include <Fonts/FreeMono9pt7b.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned int seconds = 0;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 60);
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(0);
  display.ssd1306_command(SSD1306_SETPRECHARGE);
  display.ssd1306_command(0);

  Timer1.initialize(1000000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR

  //display.setFont(&FreeMono9pt7b);

  display.clearDisplay();
}

void TimingISR()
{
  Serial.println("Interrupt");
  //updateSpd();
}

void loop() {
  LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF,
                TIMER1_ON, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  updateSpd();
}

void updateSpd() {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  
  //display.setCursor(0, 10);     // Start at top-left corner
  display.setCursor(0, 0);
  char buff[5];
  itoa(seconds, buff, 10);
  buff[4] = 0x0;
  display.println("SPD");
  display.setTextSize(4);      // Normal 1:1 pixel scale
  //display.setCursor(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10);
  //display.setCursor(SCREEN_WIDTH / 2, 20);
  display.setTextSize(5);
  display.println(seconds);
  display.display();
  seconds++;
 
}
