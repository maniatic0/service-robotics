#pragma once
#ifndef LINES_H
#define LINES_H

#include <Arduino.h>
#include "motors.h"
#define LINE_THRESHOLD 700
#define ANALOG_MAX 1023
#define LINE_SENSORS 4
#define LEFT_LEFT_LINE_SENSOR 0
#define LEFT_LINE_SENSOR 1
#define RIGHT_LINE_SENSOR 2
#define RIGHT_RIGHT_LINE_SENSOR 3
#define LINE_STOPING_CONSTANT 8/9

extern int line_read_pin[];
extern float line_reading[];
extern float line_signal[];

float ReadLineSensor(int);

void ReadLineSensors();

bool OnLine(int);

bool OnIntersection();

void LineSetup();

#endif
