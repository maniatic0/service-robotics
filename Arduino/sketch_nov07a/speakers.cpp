
#include "speakers.h"
int trigPin[] = {12,12,5};
int echoPin[] = {11,11,6};
long distance[] = {0,0,0};

void ReadSpeakers(){
    for(int i=0; i<SPEAKER_AMOUNT; i++){
        digitalWrite(trigPin[i], LOW);  // Added this line
        delayMicroseconds(2); // Added this line
        digitalWrite(trigPin[i], HIGH);
        delayMicroseconds(10); // Added this line
        digitalWrite(trigPin[i], LOW);
        distance[i] = (pulseIn(echoPin[i], HIGH)/2) / MAGIC_SPEAKER_CONSTANT;
    }
}

bool OutOfRange(int i) {
    return distance[i] >= SPEAKER_THRESHOLD || distance[i] <= 0;
}

void SpeakerSetup(){
	for(int i=0; i<SPEAKER_AMOUNT; i++){
        pinMode(trigPin[i], OUTPUT);
        pinMode(echoPin[i], INPUT);
    }
}
