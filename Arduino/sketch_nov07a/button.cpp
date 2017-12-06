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

void ButtonClickerSetup(){
  pinMode(BUTTON_PIN, INPUT);
}
