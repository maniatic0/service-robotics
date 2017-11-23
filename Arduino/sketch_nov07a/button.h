#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "configuration.h"
#include "motors.h"
#include "leds.h"
#include <Arduino.h>

#define BUTTON_PIN 13
#define CLICKER_PIN 4
#define STOPPER_PIN 5

#define CLICKER_PRESSED 20
#define STOPPER_PRESSED 20

extern bool button_state;
extern int current_button_state;
extern int last_button_state;

bool Button();

bool Clicker();

bool Stopper();

void ButtonClickerSetup();

#endif
