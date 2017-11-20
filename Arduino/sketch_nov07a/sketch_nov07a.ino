#include "Timer.h"

#include "lines.h"
#include "motors.h"
#include "leds.h"
#include "button.h"
#include "speakers.h"


#define DEBUG

#define LEFTS 1
#define RIGHTS 2
#define LEFTS_CROSS 3
#define RIGHTS_CROSS 4

#define FORWARD 0
#define LEFT_CORNER (LEFTS)
#define RIGHT_CORNER (RIGHTS)
#define LEFT_T (LEFTS)
#define RIGHT_T (RIGHTS)
#define LEFT_WEIRD (LEFTS_CROSS)
#define RIGHT_WEIRD (RIGHTS_CROSS)
#define LEFT_CROSS (LEFTS_CROSS)
#define RIGHT_CROSS (RIGHTS_CROSS)
#define TARGET 9
#define ENTRANCE 10
#define TURN 11
#define FULL_STOP 12
#define DELAY 13

#define TIMER_DELAY 5000
int dir = LEFT_CORNER;

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

/*int path[PATH_LENGTH] = {LEFT_CORNER,RIGHT_CORNER,
    LEFT_T,RIGHT_CROSS,
    RIGHT_CORNER,RIGHT_CORNER,
    LEFT_CORNER,LEFT_CORNER,
    FORWARD,RIGHT_CORNER,
    LEFT_CORNER,LEFT_CORNER,TARGET,TURN,FULL_STOP};*/
#define PATH_LENGTH 3
int path[PATH_LENGTH] = {TARGET, TURN, FULL_STOP};
int path_pos = 0;

bool on_intersection = false;
bool entering_intersection = false;
bool exiting_intersection = false;
bool top_corner = false; // If we are on top of a top_corner afer hitting the right right sensor
bool white_corner = false; // for cross intersections
bool black_corner = false; // for cross intersections
bool second_white_corner = false; // for cross intersections

Timer timer;

#define CLAWS 2 
// cm

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
        Serial.println("RightSCross");
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

//we want to turn 180 degrees for our left
void Turn() {
#ifdef DEBUG
        Serial.println("Turn");
#endif    
    /*Top corner is used just to say if it is the first time we are entering in the function.Just to be sure if the right line sensor
    is or not over the line*/
    if(!top_corner) {
      line_signal[LEFT_MOTOR] = STOP;
      line_signal[RIGHT_MOTOR] = STOP;
      top_corner = true;
    }
    else
    {
        line_signal[LEFT_MOTOR] = LEFT_TURN;
        line_signal[RIGHT_MOTOR] = RIGHT_TURN;
    }
    
    //After an intersection mark as a normal path again
    if(OnLine(RIGHT_LINE_SENSOR) && top_corner && !black_corner) black_corner = true;
    else if(!OnLine(RIGHT_LINE_SENSOR) && top_corner && black_corner && !white_corner) white_corner = true;
    else if (OnLine(LEFT_LINE_SENSOR) && top_corner && black_corner && white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        black_corner = false;
        top_corner = false;
        second_white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
} 

void Target() {
#ifdef DEBUG
        Serial.println("Target");
#endif    
    ReadSpeakers();
    NormalLineControl();
    if(distance[FRONT_SPEAKER] <= 30 + CLAWS)
    {
        if(line_signal[LEFT_MOTOR] != STOP) line_signal[LEFT_MOTOR] = int(float(STOP)-float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/30.0);
        if(line_signal[RIGHT_MOTOR] != STOP) line_signal[RIGHT_MOTOR] = int(float(STOP)+float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/30.0);
    }

    if(Clicker()){
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void DelayAfter() {
    updatePath();
    exiting_intersection = true;
    entering_intersection = false;
    top_corner = false;
}

void Delay() {
#ifdef DEBUG
        Serial.println("Delay");
#endif    

    NormalLineControl();
    if(!top_corner) {
        timer.after(TIMER_DELAY, DelayAfter);
    }
}

void LineControl() {
    on_intersection = OnIntersection() || dir == TURN || dir == DELAY || dir == TARGET;
    
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
        case LEFTS:
          LeftS();
          break;
        case RIGHTS:
          RightS();
          break;
        case LEFTS_CROSS:
          LeftSCross();
          break;
        case RIGHTS_CROSS:
          RightSCross();
          break;
        case TURN:
          Turn();
          break;
        case TARGET:
          Target();
          break;
        case DELAY:
          Delay();
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

void setup() {
    MotorSetup();
    LineSetup();
    SpeakerSetup();
    ButtonClickerSetup();

    Serial.begin(9600);              //  setup serial

    dir = path[path_pos];
    LEDsSetup();
}

void loop() {
    if(!Button()) {
      return;  
    }
    timer.update();
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
    
    Serial.print("Speaker: ");
    Serial.print(distance[FRONT_SPEAKER]);
    Serial.println(" cm"); 
#endif
}
