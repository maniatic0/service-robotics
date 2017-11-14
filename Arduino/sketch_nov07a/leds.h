
#pragma once
#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include "lines.h"
#define LED_AMOUNT 4

extern int led_pin[];


void UpdateLED(int, bool);

void UpdateLEDs();

void LEDsSetup();

void LEDsOff();

#endif