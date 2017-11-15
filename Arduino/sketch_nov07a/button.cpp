
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
            Serial.println("Stopped");
            MotorStop();
            LEDsOff();
          }
          else {
            Serial.println("Started");
            MotorStart();
            delay(200);
          }
      }
      delay(50);
    }
    last_button_state = current_button_state;
    return button_state;
}

void ButtonSetup(){
	pinMode(BUTTON_PIN, INPUT);
}