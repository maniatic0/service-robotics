
#include "button.h"

bool button_state = false;
int current_button_state = 0;
int last_button_state = 0;

bool Button(){
    current_button_state = digitalRead(BUTTON_PIN);
    if(current_button_state != last_button_state){
      if (current_button_state == HIGH)
      {
          button_state = !button_state;
          if (!button_state){
#ifdef DEBUG
            Serial.println("Stopped");
#endif
            MotorStop();
            LEDsOff();
          }
          else {
#ifdef DEBUG
            Serial.println("Started");
#endif
            MotorStart();
            delay(200);
          }
      }
      delay(50);
    }
    last_button_state = current_button_state;
    return button_state;
}

bool clicker_state = false;
int current_clicker_state = 0;
int last_clicker_state = 0;

bool Clicker(){
    current_clicker_state = digitalRead(CLICKER_PIN);
    if(current_clicker_state != last_clicker_state){
      if (current_clicker_state == HIGH)
      {
          clicker_state = !clicker_state;
          if (!clicker_state){
#ifdef DEBUG
            Serial.println("Click Off");
#endif
          }
          else {
#ifdef DEBUG
            Serial.println("Click On");
#endif
          }
      }
      delay(50);
    }
    last_clicker_state = current_clicker_state;
    return clicker_state;
}

void ButtonClickerSetup(){
	pinMode(BUTTON_PIN, INPUT);
  pinMode(CLICKER_PIN, INPUT);
  last_clicker_state = digitalRead(CLICKER_PIN);
}
