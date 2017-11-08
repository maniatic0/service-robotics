#include <Servo.h>

#define LEFT_FORWARD 0 
#define STOP 90 
#define LEFT_BACKWARD 180 
#define RIGHT_FORWARD 180 
#define RIGHT_BACKWARD 0
#define LEFT_TURN 110 
#define RIGHT_TURN 110 
#define MOTORS 2
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1


Servo left_servo;  // create servo object to control a servo
Servo right_servo;  // create servo object to control a servo
int servoPin[] = {9, 10};
float motor_signal[MOTORS] = {0,0};

// twelve servo objects can be created on most boards

int outSignal = 90;    // variable to store the servo position
int inSignal = 90;
float test;
int readPin = 0;


#define LINE_THRESHOLD 400
#define ANALOG_MAX 1023
#define LINE_SENSORS 4
#define LEFT_LEFT_LINE_SENSOR 0
#define LEFT_LINE_SENSOR 1
#define RIGHT_LINE_SENSOR 2
#define RIGHT_RIGHT_LINE_SENSOR 3
#define LINE_STOPING_CONSTANT 8/9

int line_read_pin[LINE_SENSORS] = {0, 1, 2, 3};
float line_reading[LINE_SENSORS] = {0, 0, 0, 0};
float line_signal[MOTORS] = {0, 0};


int trigPin[] = {1,3,5};
int echoPin[] = {2,4,6};
long distance[] = {0,0,0};
#define MAGIC_SPEAKER_CONSTANT 29.1
#define SPEAKER_AMOUNT 3
#define LEFT_SPEAKER 0
#define FRONT_SPEAKER 1
#define RIGHT_SPEAKER 2
#define SPEAKER_THRESHOLD 30

#define BUTTON_PIN 7

bool button_state = false;

#define FORWARD 0
#define LEFT_CORNER 1
#define RIGHT_CORNER 2
#define LEFT_CROSS 3
#define RIGHT_CROSS 4
#define LEFT_T 5
#define RIGHT_T 6
#define LEFT_WEIRD 7
#define RIGHT_WEIRD 8
#define TARGET 9
#define ENTRANCE 10
#define TURN 11
int dir = 0;

bool on_intersection = false;
bool entering_intersection = false;
bool exiting_intersection = false;
bool top_corner = false; // If we are on top of a top_corner afer hitting the right right sensor
bool white_corner = false; // for cross intersections
bool black_corner = false; // for cross intersections
bool second_white_corner = false; // for cross intersections


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


void NormalLineControl() {
    if (OnLine(LEFT_LINE_SENSOR))
    {
        line_signal[LEFT_MOTOR] = STOP * LINE_STOPING_CONSTANT;
    }
    else
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
    }

    if (OnLine(RIGHT_LINE_SENSOR))
    {
        line_signal[RIGHT_MOTOR] = STOP  * (2 - LINE_STOPING_CONSTANT) ;
    }
    else
    {
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
}

void Forward(){
    line_signal[LEFT_MOTOR] = LEFT_FORWARD;
    line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;

    //After an intersection mark as a normal path again
    if (!on_intersection && entering_intersection && !exiting_intersection)
    {
        exiting_intersection = true;
        entering_intersection = false;
    }
}

void LeftCorner(){
    if (!top_corner)
    {
        line_signal[LEFT_MOTOR] = STOP;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = STOP;
    }
    
    //After an intersection mark as a normal path again
    if (OnLine(RIGHT_RIGHT_LINE_SENSOR) && !top_corner)
    {
        top_corner = true;
    }

    if (OnLine(LEFT_LINE_SENSOR) && top_corner && entering_intersection && !exiting_intersection)
    {
        exiting_intersection = true;
        entering_intersection = false;
        top_corner = false;
    }
}

void RightCorner(){
    if (!top_corner)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = STOP;
    }
    else
    {
        line_signal[LEFT_MOTOR] = STOP;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    
    //After an intersection mark as a normal path again
    if (OnLine(LEFT_LEFT_LINE_SENSOR) && !top_corner)
    {
        top_corner = true;
    }

    if (OnLine(RIGHT_LINE_SENSOR) && top_corner && entering_intersection && !exiting_intersection)
    {
        exiting_intersection = true;
        entering_intersection = false;
        top_corner = false;
    }
}


void LeftCross(){
    // We haven't reached half of the turn
    if (!(white_corner && black_corner && second_white_corner))
    {
        line_signal[LEFT_MOTOR] = STOP;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else
    {
        LeftCorner();
    }
    
    if (!OnLine(RIGHT_RIGHT_LINE_SENSOR))
    {
        if (!white_corner)
        {
            white_corner = true;
        }
        else if(!second_white_corner && black_corner) {
            second_white_corner = true;
        }
    }
    else {
        if (!black_corner && white_corner)
        {
            black_corner = true;
        }
    }
}

void RightCross(){
    // We haven't reached half of the turn
    if (!(white_corner && black_corner && second_white_corner))
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = STOP;
    }
    else
    {
        RightCorner();
    }
    
    if (!OnLine(LEFT_LEFT_LINE_SENSOR))
    {
        if (!white_corner)
        {
            white_corner = true;
        }
        else if(!second_white_corner && black_corner) {
            second_white_corner = true;
        }
    }
    else {
        if (!black_corner && white_corner)
        {
            black_corner = true;
        }
    }
}


void LeftT(){
    // We haven't reached half of the turn
    if (!white_corner)
    {
        line_signal[LEFT_MOTOR] = STOP;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else
    {
        LeftCorner();
    }
    
    if (!OnLine(RIGHT_RIGHT_LINE_SENSOR))
    {
        if (!white_corner)
        {
            white_corner = true;
        }
    }
}

void RightT(){
    // We haven't reached half of the turn
    if (!white_corner)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = STOP;
    }
    else
    {
        RightCorner();
    }
    
    if (!OnLine(LEFT_LEFT_LINE_SENSOR))
    {
        if (!white_corner)
        {
            white_corner = true;
        }
    }
}

void LeftWeird(){
    // We haven't reached half of the turn
    if (!(white_corner && black_corner))
    {
        line_signal[LEFT_MOTOR] = STOP;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else
    {
        LeftCorner();
    }
    
    if (!OnLine(RIGHT_RIGHT_LINE_SENSOR))
    {
        if (!white_corner && black_corner)
        {
            white_corner = true;
        }
    }
    else{
        if (!black_corner)
        {
            black_corner = true;
        }
    }
}

void RightWeird(){
    // We haven't reached half of the turn
    if (!(white_corner && black_corner))
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = STOP;
    }
    else
    {
        RightCorner();
    }
    
    if (!OnLine(LEFT_LEFT_LINE_SENSOR))
    {
        if (!white_corner && black_corner)
        {
            white_corner = true;
        }
    }
    else {
        if (!black_corner)
        {
            black_corner = true;
        }
    }
}
//we want to turn 180 degrees for our left
void Turn() {
    
    line_signal[LEFT_MOTOR] = LEFT_TURN;
    line_signal[RIGHT_MOTOR] = RIGHT_TURN;
    
    if (OnLine(LEFT_LEFT_LINE_SENSOR))
    {
        if (!black_corner)
        {
            black_corner = true;
        }
    }
    
    if (OnLine(RIGHT_LINE_SENSOR) && black_corner && entering_intersection && !exiting_intersection)
    {
        exiting_intersection = true;
        entering_intersection = false;
        black_corner = false;
    }

} 

void LineControl() {
    on_intersection = OnIntersection();
    //End of the intersection
    if (!on_intersection && !(entering_intersection && !exiting_intersection))
    {
        NormalLineControl();
        return;
    }

    //If we do not want to make the NormalLineControl and we are still on the Intersection. Just mark the entrance on the Intersection
    if (!entering_intersection)
    {
        entering_intersection = true;
        exiting_intersection = false;
        top_corner = false;
        white_corner = false;
        black_corner = false;
        second_white_corner = false;
    }


    switch (dir) {
        case FORWARD:
          Forward();
          break;
        case LEFT_CORNER:
          LeftCorner();
          break;
        case RIGHT_CORNER:
          RightCorner();
          break;
        case LEFT_CROSS:
          LeftCross();
          break;
        case RIGHT_CROSS:
          RightCross();
          break;
        case LEFT_T:
          LeftT();
          break;
        case RIGHT_T:
          RightT();
          break;
        case LEFT_WEIRD:
          LeftWeird();
          break;
        case RIGHT_WEIRD:
          RightWeird();
          break;
        case TURN:
          Turn();
          break;
        default:
          break;
    }
}


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


void MotorControl(){
    ReadLineSensors();
    LineControl();
    ReadSpeakers();


    motor_signal[LEFT_MOTOR] = line_signal[LEFT_MOTOR];
    motor_signal[RIGHT_MOTOR] = line_signal[RIGHT_MOTOR];

    if (OutOfRange(LEFT_SPEAKER) && OutOfRange(RIGHT_SPEAKER))
    {
        motor_signal[LEFT_MOTOR] = STOP;
        motor_signal[RIGHT_MOTOR] = STOP;
    }
    else if (!OutOfRange(FRONT_SPEAKER)) 
    {
        motor_signal[LEFT_MOTOR] = STOP;
        motor_signal[RIGHT_MOTOR] = STOP;
    }


    left_servo.write(motor_signal[LEFT_MOTOR]);
    right_servo.write(motor_signal[RIGHT_MOTOR]);
}

void Button(){
    if (digitalRead(BUTTON_PIN) == HIGH)
    {
        button_state = !button_state;
    }
}

void setup() {
    left_servo.attach(servoPin[LEFT_MOTOR]);
    right_servo.attach(servoPin[RIGHT_MOTOR]);
    left_servo.write(STOP);
    right_servo.write(STOP);

    for(int i=0; i<LINE_SENSORS; i++){
        pinMode(line_read_pin[i],INPUT);
    }

    for(int i=0; i<SPEAKER_AMOUNT; i++){
        pinMode(trigPin[i], OUTPUT);
        pinMode(echoPin[i], INPUT);
    }

    pinMode(BUTTON_PIN, INPUT);

    Serial.begin(9600);              //  setup serial
}

void loop() {
    while(!button_state){
        Button();
        if (button_state)
        {
            Serial.println("Started");
            delay(200);
            break;
        }
    }
    while(button_state){
        Button();
        if (!button_state)
        {
            Serial.println("Stopped");
            left_servo.write(STOP);
            right_servo.write(STOP);
            delay(200);
            break;
        }
        MotorControl();
        Serial.print("Left motor:");
        Serial.println(motor_signal[LEFT_MOTOR]);
        Serial.print("Right motor:");
        Serial.println(motor_signal[RIGHT_MOTOR]);
        delay(100); 
    } 
}
