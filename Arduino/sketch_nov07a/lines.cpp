#include "lines.h"

int line_read_pin[LINE_SENSORS] = {0, 1, 2, 3};
float line_reading[LINE_SENSORS] = {0, 0, 0, 0};
float line_signal[MOTORS] = {0, 0};

float ReadLineSensor(int i){
    return float(analogRead(line_read_pin[i]) - LINE_THRESHOLD) / float(ANALOG_MAX);
}

void ReadLineSensors() {
    for(int i=0; i<LINE_SENSORS; i++){
        line_reading[i] = ReadLineSensor(i);
    }
}

bool OnLine(int i) {
    return line_reading[i] >= 0;
}

bool OnIntersection(){
    return OnLine(LEFT_LEFT_LINE_SENSOR) || OnLine(RIGHT_RIGHT_LINE_SENSOR);
}

void LineSetup() {
    for(int i=0; i<LINE_SENSORS; i++){
        pinMode(line_read_pin[i],INPUT);
    }  
}
