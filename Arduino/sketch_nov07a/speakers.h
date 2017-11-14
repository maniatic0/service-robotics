
#pragma once
#ifndef SPEAKERS_H
#define SPEAKERS_H

#include <Arduino.h>

#define MAGIC_SPEAKER_CONSTANT 29.1
#define SPEAKER_AMOUNT 3
#define LEFT_SPEAKER 0
#define FRONT_SPEAKER 1
#define RIGHT_SPEAKER 2
#define SPEAKER_THRESHOLD 30

extern int trigPin[];
extern int echoPin[];
extern long distance[];

void ReadSpeakers();

bool OutOfRange(int);

void SpeakerSetup();

#endif