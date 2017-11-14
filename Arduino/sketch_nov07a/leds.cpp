#include "leds.h"

int led_pin[LED_AMOUNT] = {5,4,3,2};


void UpdateLED(int i, bool status) {
    if (status)
    {
        digitalWrite(led_pin[i], HIGH);
        return;
    }
    digitalWrite(led_pin[i], LOW);
}

void UpdateLEDs(){
    UpdateLED(0, OnLine(LEFT_LEFT_LINE_SENSOR));
    UpdateLED(1, OnLine(LEFT_LINE_SENSOR));
    UpdateLED(2, OnLine(RIGHT_LINE_SENSOR));
    UpdateLED(3, OnLine(RIGHT_RIGHT_LINE_SENSOR));
}

void LEDsSetup(){
	LEDsOff();
}

void LEDsOff() {
	for(int i=0; i<LED_AMOUNT; i++){
        pinMode(led_pin[i], OUTPUT);
        digitalWrite(led_pin[i], LOW);
    }
}