#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "motors.h"
#include "leds.h"
#include <Arduino.h>

#define BUTTON_PIN 7
#define CLICKER_PIN 8

extern bool button_state;
extern int current_button_state;
extern int last_button_state;

extern bool clicker_state;
extern int clicker_button_state;
extern int last_clicker_state;

bool Button();

bool Clicker();

void ButtonClickerSetup();

#endif
