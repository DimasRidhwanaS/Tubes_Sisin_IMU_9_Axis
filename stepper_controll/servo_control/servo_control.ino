#include <Servo.h>

float servo1_angle, servo2_angle, servo3_angle;
float alpha, beta, gamma, theta, delta;                         // Degrees between links -- see calculation on tab
float alpha_rad, beta_rad, gamma_rad, theta_rad, delta_rad;     // Degrees between links -- see calculation on tab
float a,b,c;                                                    // Arm Length     : a (first link), b (second link), c (diagonal)
float x,y,z;                                                    // IMU Coordinate 
float pi = 3.1415926535;
float max_length;
float test;

Servo servo1;
Servo servo2;
Servo servo3;

void kinematics_calculation(int a, int b, int x, int y, int z){
  c           = sqrt(sq(x)+sq(y)+sq(z));
  if (c>=max_length){
  	c = max_length-2;
  }
  
  theta_rad   = atan(z/x);
  beta_rad    = acos((sq(a)+sq(c)-sq(b))/(2*a*c));
  gamma_rad   = acos((sq(a)+sq(b)-sq(c))/(2*a*b));
  float test_rad  = acos(0.5);
  float test_deg  = test_rad*180/pi;

  if (y>0){
    delta_rad = atan(x/y);
  } else if (y==0){
	delta_rad = pi/2;  
  } else {
    delta_rad = pi+atan(x/y);
  }

  beta        = beta_rad * 180 / pi; 
  gamma       = gamma_rad * 180 / pi;
  delta       = delta_rad * 180 / pi;
  theta       = theta_rad * 180 / pi;
  test		  = (beta_rad+theta_rad) * 180 / pi;
}


void testing(){
  Serial.print("sq_a  :");
  Serial.println(sq(a));
  Serial.print("sq_b  :");
  Serial.println(sq(a));
  Serial.print("c  :");
  Serial.println(c);
  
  Serial.print("beta_rad  :");
  Serial.println(beta_rad);
  Serial.print("gamma_rad  :");
  Serial.println(gamma_rad);
  Serial.print("theta_rad  :");
  Serial.println(theta_rad);
  Serial.print("delta_rad  :");
  Serial.println(delta_rad);
  
  Serial.println("     ");
  
  Serial.print("beta_rad + theta_rad  :");
  Serial.println(beta_rad+theta_rad);
  Serial.print("beta_theta_deg:");
  Serial.println(test);
}

void output(){
  Serial.print("servo1_angle  :");
  Serial.println(servo1_angle);
  Serial.print("servo2_angle  :");
  Serial.println(servo2_angle);
  Serial.print("servo3_angle  :");
  Serial.println(servo3_angle);

  Serial.println("---------------------------------");
  Serial.println("   ");
}

void servo_test(){
  int degree_test = 0;
  // Serial.print("Servo Testing----------");
  // servo1.write(0);
  // servo2.write(0);
  // servo3.write(0);
  // delay(1000);
  servo1.write(180-degree_test);
  servo2.write(degree_test);
  servo3.write(180-degree_test);
  delay(1000);  
}

void setup(){
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
}

void loop(){
  Serial.println("Starting Program");

  // predefine a and b length
  a = 40;
  b = 40;
  max_length = a + b;

  // IMU reading
  x = 0;		// 
  y = 0;		// base 0 deg
  z = 30;		// 

  Serial.println("Attempt Calculation");
  kinematics_calculation(a,b,x,y,z);
  Serial.println("Calculation Done");
  servo1_angle = delta;
  servo2_angle = theta+beta;
  servo3_angle = gamma;


  servo1.write(180-servo1_angle);             // Base Servo
  servo2.write(servo2_angle);         // First Link Adjusted
  servo3.write(180-servo3_angle);         // Second Link Adujusted
  delay(1000);
  
  // servo_test();
  // testing();
  output();
}



