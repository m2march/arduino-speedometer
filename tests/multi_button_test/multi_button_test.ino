#include <avr/interrupt.h>

int left = 0;
int right = 0;

class Debouncer {

  public:

    // Max debounce time in microseconds
    const static unsigned long PRESS_DELAY = 200L * 1000L;


    Debouncer(int pin, bool natural_state);

    /** Post: true si fue presionado sin tener en cuenta el debouncing */
    bool checkInterrupt();


  private:
    int _pin;
    bool _natural_state;
    bool _debouncing;
    unsigned long _last_change_micros;

};

Debouncer::Debouncer(int pin, bool natural_state) : _pin(pin), _natural_state(natural_state),
  _debouncing(false), _last_change_micros(0L) {};

bool Debouncer::checkInterrupt() {
  if (digitalRead(_pin) != _natural_state) {
    if (!_debouncing) {
      _last_change_micros = micros(); 
      _debouncing = true;
      return true;
    } 
  } else {
    if (_debouncing and (micros() - _last_change_micros) > PRESS_DELAY) {
      _debouncing = false;
    }
  }
  return false;
}

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

Debouncer pin10(10, HIGH);
Debouncer pin11(11, HIGH);

void setup()
{
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pciSetup(10);
  pciSetup(11);  
  Serial.begin(9600);
}

void loop()
{
//Serial.print(left);
//Serial.print("\t");
//Serial.println(right);
Serial.print(digitalRead(10));
Serial.print("\t");
Serial.println(digitalRead(11));
delay(100);
}

ISR(PCINT0_vect)
{
  Serial.print(digitalRead(10));
  Serial.print("\t");
  Serial.println(digitalRead(11));
  //Serial.println("Int");
 if (pin10.checkInterrupt()) {
  left++;
 }
 if (pin11.checkInterrupt()) {
  right++;
 }
}
