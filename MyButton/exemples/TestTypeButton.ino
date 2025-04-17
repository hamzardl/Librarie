#include <Arduino.h>
#include "MyButton.h"

const int GPIO_BUTTON_TO_USE = 15;
#define MYBUTTON_NO_CLICK 0 
#define MYBUTTON_SHORT_CLICK 2 
#define MYBUTTON_LONG_CLICK 3 
#define MYBUTTON_DOUBLE_CLICK 4 
#define DebounceDelay 50
#define LongPressDuration 1000
#define DoubleClickMaxDelay 400

MyButton button(GPIO_BUTTON_TO_USE, MYBUTTON_NO_CLICK);

void setup() {
  Serial.begin(9600);
  button.setButtonDebounceDelay(DebounceDelay);
  button.setButtonLongPressDuration(LongPressDuration);
  button.setButtonDoubleClickMaxDelay(DoubleClickMaxDelay);
}

void loop() {
  int action = button.checkMyButton();
  switch (action) {
    case MYBUTTON_SHORT_CLICK:
      Serial.println("Relâché (court)");
      break;
    case MYBUTTON_LONG_CLICK:
      Serial.println("Appui long ");
      break;
    case MYBUTTON_DOUBLE_CLICK:
      Serial.println("Double clic ");
      break;
  }
}
