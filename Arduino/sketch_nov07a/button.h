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

#define ANALOG_CLICKER_TRESHOLD 120
#define CLICKER_PRESSED 60
#define STOPPER_PRESSED 60

extern bool button_state;
extern int current_button_state;
extern int last_button_state;

extern bool clicker_state;
extern int clicker_button_state;
extern int last_clicker_state;

extern bool stopper_state;
extern int stopper_button_state;
extern int last_stopper_state;

bool Button();

bool Clicker();

bool Stopper();

void ButtonClickerSetup();

#endif
