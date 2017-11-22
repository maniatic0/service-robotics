
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
    current_clicker_state = analogRead(CLICKER_PIN);
    return current_clicker_state <= CLICKER_PRESSED;
    /*
    if(abs(current_clicker_state - last_clicker_state) >= ANALOG_CLICKER_TRESHOLD){
      if (current_clicker_state <= CLICKER_PRESSED)
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
      last_clicker_state = current_clicker_state;
    }
   
    return clicker_state;*/
}

bool stopper_state = false;
int current_stopper_state = 0;
int last_stopper_state = 0;

bool Stopper(){
    current_stopper_state = analogRead(STOPPER_PIN);
    return current_stopper_state <= STOPPER_PRESSED;
    /*
    if(abs(current_stopper_state - last_stopper_state) >= 0){
      if (current_stopper_state <= STOPPER_PRESSED)
      {
          stopper_state = !stopper_state;
          if (!stopper_state){
#ifdef DEBUG
            Serial.println("Stopper Off");
#endif
          }
          else {
#ifdef DEBUG
            Serial.println("Stopper On");
#endif
          }
      }
      else {
        Serial.println("NOPE");
      }
      delay(50);
      last_stopper_state = current_stopper_state;
    }
    return stopper_state;*/
}

void ButtonClickerSetup(){
	pinMode(BUTTON_PIN, INPUT);
  pinMode(CLICKER_PIN, INPUT);
  pinMode(STOPPER_PIN, INPUT);
  last_clicker_state = digitalRead(CLICKER_PIN);
  last_stopper_state = digitalRead(STOPPER_PIN);
}
