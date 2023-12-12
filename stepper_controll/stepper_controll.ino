#include <Stepper.h>
#include <Servo.h>

// Stepper Setup
const int stepsPerRevolution = 500;

int base[4] = {4, 5, 6, 7};
int link1[4] = {8, 9, 10, 11};  // Replace with the correct pin numbers
int link2[4] = {A5, A4, A3, A2};  // Replace with the correct pin numbers
// int grip[4] = {20, 21, 22, 23};  // Replace with the correct pin numbers

Stepper stepper_base(stepsPerRevolution, base[0], base[1], base[2], base[3]);
Stepper stepper_link1(stepsPerRevolution, link1[0], link1[1], link1[2], link1[3]);
Stepper stepper_link2(stepsPerRevolution, link2[0], link2[1], link2[2], link2[3]);
// Stepper stepper_grip(stepsPerRevolution, grip[0], grip[1], grip[2], grip[3]);

// Servo Setup (we dont use it)
Servo myservo;
int pos = 0;

// Safety
int safe_switch = 3;

// Servo control
void move_servo(Servo &servo_name, int pos) {
  servo_name.write(pos);
  delay(15);
}

// Stepper Control
void move_stepper(Stepper &stepper_name, int steps) {
  stepper_name.step(steps);
}

int conversion (float angle){
  return angle*100/360;         
  /*
    100 is steps per revolution for this stepper, I dont Understand although I already 
    put 500 Steps per revolution it just do 5 revolution if I execute it
  */
}

void setup() {
  myservo.attach(9);  
  stepper_base.setSpeed(15);            // in RPM
  stepper_link1.setSpeed(50);           // in RPM best not trembling =30 

  stepper_link2.setSpeed(15);           // in RPM
  // stepper_grip.setSpeed(60);         // in RPM

  // SAFE switch declaration
  pinMode(safe_switch, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  if (digitalRead(safe_switch) == LOW){
    // Replace this with the input data from ESP32
    float servo1_angle = 60;  
    float servo2_angle = 180;
    float servo3_angle = 60;
    float servo4_angle = 60;

    int stepper_base_steps    = conversion(servo1_angle);
    int stepper_link1_steps   = conversion(servo2_angle);
    int stepper_link2_steps   = conversion(servo3_angle);
    int stepper_grip_steps    = conversion(servo4_angle);

    move_stepper(stepper_base, stepper_link1_steps);
    move_stepper(stepper_link1, 500);


    move_stepper(stepper_link2, stepper_link1_steps);
    // move_stepper(stepper_grip, stepper_link1_steps);
    delay(1000);
  } 
}
 