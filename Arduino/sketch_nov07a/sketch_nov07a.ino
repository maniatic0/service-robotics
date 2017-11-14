#include "lines.h"
#include "motors.h"
#include "leds.h"


#define DEBUG

#define BUTTON_PIN 7

bool button_state = false;
int current_button_state = 0;
int last_button_state = 0;


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
#define FULL_STOP 12
int dir = RIGHT_CROSS;
#define PATH_LENGTH 13

/*int path[PATH_LENGTH] = {LEFT_CORNER, LEFT_CROSS, FULL_STOP};*/
/*
int path[PATH_LENGTH] = {LEFT_CORNER, RIGHT_CORNER, FULL_STOP};*/

/*
int path[PATH_LENGTH] = {LEFT_CORNER, RIGHT_CORNER,
    RIGHT_T,LEFT_CORNER,
    RIGHT_T,RIGHT_CORNER,
    RIGHT_CORNER,LEFT_CORNER,
    LEFT_CORNER,LEFT_CORNER,
    LEFT_CORNER,RIGHT_CORNER,
    RIGHT_CORNER, FULL_STOP};*/

int path[PATH_LENGTH] = {LEFT_CORNER,RIGHT_CORNER,
    LEFT_T,RIGHT_CROSS,
    RIGHT_CORNER,RIGHT_CORNER,
    LEFT_CORNER,LEFT_CORNER,
    FORWARD,RIGHT_CORNER,
    LEFT_CORNER,LEFT_CORNER,FULL_STOP};

int path_pos = 0;

bool on_intersection = false;
bool entering_intersection = false;
bool exiting_intersection = false;
bool top_corner = false; // If we are on top of a top_corner afer hitting the right right sensor
bool white_corner = false; // for cross intersections
bool black_corner = false; // for cross intersections
bool second_white_corner = false; // for cross intersections

void updatePath() {
    path_pos++;
    if (path_pos >= PATH_LENGTH)  path_pos = 0;
    dir = path[path_pos];
}

void NormalLineControl() {
#ifdef DEBUG
        Serial.println("Normal Line");
#endif
    if (OnLine(LEFT_LINE_SENSOR))
    {
        line_signal[LEFT_MOTOR] = STOP;
    }
    else
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
    }

    if (OnLine(RIGHT_LINE_SENSOR))
    {
        line_signal[RIGHT_MOTOR] = STOP;
    }
    else
    {
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
}

void Forward(){
#ifdef DEBUG
        Serial.println("Forward");
#endif
    line_signal[LEFT_MOTOR] = LEFT_FORWARD;
    line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;

    //After an intersection mark as a normal path again
    if (!on_intersection && entering_intersection && !exiting_intersection)
    {
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void LeftS(){
#ifdef DEBUG
        Serial.println("LeftS");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(LEFT_LEFT_LINE_SENSOR) && !white_corner) white_corner = true;
      
      line_signal[LEFT_MOTOR] = LEFT_BACKWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }

    //After an intersection mark as a normal path again
    if (OnLine(RIGHT_LINE_SENSOR) && white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void RightS(){
#ifdef DEBUG
        Serial.println("RightS");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(RIGHT_RIGHT_LINE_SENSOR) && !white_corner) white_corner = true;
      
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_BACKWARD;
    }

    //After an intersection mark as a normal path again
    if (OnLine(LEFT_LINE_SENSOR) && white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void LeftSCross(){
#ifdef DEBUG
        Serial.println("LeftSCross");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(LEFT_LEFT_LINE_SENSOR) && !white_corner) white_corner = true;
      line_signal[LEFT_MOTOR] = LEFT_BACKWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    
    //After an intersection mark as a normal path again
    if(OnLine(RIGHT_LINE_SENSOR) && white_corner && !black_corner) black_corner = true;
    else if(!OnLine(RIGHT_LINE_SENSOR) && white_corner && black_corner && !second_white_corner) second_white_corner = true;
    else if (OnLine(RIGHT_LINE_SENSOR) && white_corner && black_corner && second_white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        black_corner = false;
        second_white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}


void RightSCross(){
#ifdef DEBUG
        Serial.println("LeftSCross");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(RIGHT_RIGHT_LINE_SENSOR) && !white_corner) white_corner = true;
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_BACKWARD;
    }
    
    //After an intersection mark as a normal path again
    if(OnLine(LEFT_LINE_SENSOR) && white_corner && !black_corner) black_corner = true;
    else if(!OnLine(LEFT_LINE_SENSOR) && white_corner && black_corner && !second_white_corner) second_white_corner = true;
    else if (OnLine(LEFT_LINE_SENSOR) && white_corner && black_corner && second_white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        black_corner = false;
        second_white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}


void LeftCorner(){
#ifdef DEBUG
        Serial.println("Left Corner");
#endif
    if (!top_corner)
    {
        line_signal[LEFT_MOTOR] = 100;
        line_signal[RIGHT_MOTOR] = 110;
    }
    else
    {
        line_signal[LEFT_MOTOR] = 70;
        line_signal[RIGHT_MOTOR] = 90;
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
        updatePath();
    }
}

void RightCorner(){
#ifdef DEBUG
        Serial.println("Right Corner");
#endif
    if (!top_corner)
    {
        line_signal[LEFT_MOTOR] = 60;
        line_signal[RIGHT_MOTOR] = 82;
    }
    else
    {
        line_signal[LEFT_MOTOR] = 90;
        line_signal[RIGHT_MOTOR] = 110;
  
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
        updatePath();
    }
}


void LeftCross(){
#ifdef DEBUG
        Serial.println("Left Cross");
#endif
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
#ifdef DEBUG
        Serial.println("Right Cross");
#endif
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
#ifdef DEBUG
        Serial.println("Left T");
#endif
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
#ifdef DEBUG
        Serial.println("Right T");
#endif
    // We haven't reached half of the turn
    if (!white_corner)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD+22;
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
#ifdef DEBUG
        Serial.println("Left Weird");
#endif
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
#ifdef DEBUG
        Serial.println("Right Weird");
#endif
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
#ifdef DEBUG
        Serial.println("Turn");
#endif
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
        left_servo.write(STOP);
        right_servo.write(STOP);
        entering_intersection = true;
        exiting_intersection = false;
        top_corner = false;
        white_corner = false;
        black_corner = false;
        second_white_corner = false;
#ifdef DEBUG
        Serial.println("Entering Intersection");
#endif
    }


    switch (dir) {
        case FORWARD:
          Forward();
          break;
        case LEFT_CORNER:
          LeftS();
          break;
        case RIGHT_CORNER:
          RightS();
          break;
        case LEFT_CROSS:
          LeftSCross();
          break;
        case RIGHT_CROSS:
          RightSCross();
          break;
        case LEFT_T:
          LeftS();
          break;
        case RIGHT_T:
          RightS();
          break;
        case LEFT_WEIRD:
          LeftSCross();
          break;
        case RIGHT_WEIRD:
          RightSCross();
          break;
        case TURN:
          Turn();
          break;
        case FULL_STOP:
          MotorStop();
          updatePath();
          break;
        default:
          break;
    }
}


void MotorControl(){
    ReadLineSensors();
    LineControl();

    motor_signal[LEFT_MOTOR] = line_signal[LEFT_MOTOR];
    motor_signal[RIGHT_MOTOR] = line_signal[RIGHT_MOTOR];

    left_servo.write(motor_signal[LEFT_MOTOR]);
    right_servo.write(motor_signal[RIGHT_MOTOR]);
}

void Button(){
    current_button_state = digitalRead(BUTTON_PIN);
    if(current_button_state != last_button_state){
      if (current_button_state == HIGH)
      {
          button_state = !button_state;
          if (!button_state){
            Serial.println("Stopped");
            MotorStop();
            LEDsOff();
          }
          else {
            Serial.println("Started");
            MotorStart();
            delay(200);
          }
      }
      delay(50);
    }
    last_button_state = current_button_state;
}

void setup() {
    MotorSetup();
    LineSetup();
    // SpeakerSetup();

    pinMode(BUTTON_PIN, INPUT);

    Serial.begin(9600);              //  setup serial

    dir = path[path_pos];
    LEDsSetup();
}

void loop() {
    Button();
    if(!button_state) {
      return;  
    }
    MotorControl();
    UpdateLEDs();
#ifdef DEBUG
    Serial.print("Left motor:");
    Serial.print(motor_signal[LEFT_MOTOR]);
    Serial.print(" Right motor:");
    Serial.println(motor_signal[RIGHT_MOTOR]);
    
    Serial.print("Line Sensors: ");
    Serial.print(OnLine(LEFT_LEFT_LINE_SENSOR));
    Serial.print(" ");
    Serial.print(OnLine(LEFT_LINE_SENSOR));
    Serial.print(" ");
    Serial.print(OnLine(RIGHT_LINE_SENSOR));
    Serial.print(" ");
    Serial.print(OnLine(RIGHT_RIGHT_LINE_SENSOR));
    Serial.println(" "); 
#endif
}
