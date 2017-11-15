#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "motors.h"
#include "leds.h"
#include <Arduino.h>

#define BUTTON_PIN 7

extern bool button_state;
extern int current_button_state;
extern int last_button_state;

bool Button();

void ButtonSetup();

#endif