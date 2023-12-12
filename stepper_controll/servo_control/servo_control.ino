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
  
  // c limitter
  if (c>=max_length){
  	c = max_length;
  }
  // z limitter
  if (z<0){
    z = 0;
  }
  // x limitter
  if (x<=0){
    x = 1;
  }

  theta_rad   = atan2(z, x);
  beta_rad    = acos((sq(a)+sq(c)-sq(b))/(2*a*c));
  gamma_rad   = acos((sq(a)+sq(b)-sq(c))/(2*a*b));
  float test_rad  = acos(0.5);
  float test_deg  = test_rad*180/pi;

  if (y==0){
	  delta_rad = pi/2;
  } else {
    delta_rad = atan2(x,y);
  }

  beta        = beta_rad * 180 / pi; 
  gamma       = gamma_rad * 180 / pi;
  delta       = delta_rad * 180 / pi;
  theta       = theta_rad * 180 / pi;
  test		    = (beta_rad+theta_rad) * 180 / pi;
}


void testing(){
  // Serial.print("c :  ");
  // Serial.println(c);

  
  // Serial.print("x :  ");
  // Serial.println(x);
  // Serial.print("y :  ");
  // Serial.println(y);
  // Serial.print("z :  ");
  // Serial.println(z);

  // Serial.print("sq_a  :");
  // Serial.println(sq(a));
  // Serial.print("sq_b  :");
  // Serial.println(sq(a));
  // Serial.print("c  :");
  // Serial.println(c);
  
  // Serial.print("beta_rad  :");
  // Serial.println(beta_rad);
  // Serial.print("gamma_rad  :");
  // Serial.println(gamma_rad);
  // Serial.print("theta_rad  :");
  // Serial.println(theta_rad);
  // Serial.print("delta_rad  :");
  // Serial.println(delta_rad);
  
  // Serial.println("     ");
  

  Serial.print("theta  :");
  Serial.println(theta);
  // Serial.print("beta  :");
  // Serial.println(beta);
  // Serial.print("gamma  :");
  // Serial.println(gamma);
  // Serial.print("delta  :");
  // Serial.println(delta);

  // Serial.print("beta_rad + theta_rad  :");
  // Serial.println(beta_rad+theta_rad);
  Serial.print("beta_theta_deg:");
  Serial.println(test);
  delay(1000);
}

void output(){
  Serial.print(servo1_angle);
  Serial.print("        ");
  Serial.print(servo2_angle);
  Serial.print("        ");
  Serial.println(servo3_angle);
  delay(15);
}

void servo_test(){
  int degree_test = 0;
  // Serial.print("Servo Testing----------");
  servo1.write(90);
  servo2.write(90);
  servo3.write(180);
  // delay(1000); 
  // servo1.write(0);
  // delay(1000);
  // servo3.write(0);
  // delay(1000);
  // servo1.write(180-degree_test);
  // servo2.write(degree_test);
  // servo3.write(180-degree_test);
  // delay(1000);

  // Serv0 1 ->
  // Servo 1 -> Maks 160
}

void move_servo(){
  servo1.write(servo1_angle);             // Base Servo
  servo2.write(servo2_angle);         // First Link Adjusted
  servo3.write(servo3_angle);         // Second Link Adujusted
  delay(100);
}

void setup(){
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
}

void loop(){
  // Serial.println("Starting Program");

  // predefine a and b length
  a = 13;
  b = 11;
  max_length = a + b;

  // IMU reading
  x = 0;		// 
  y = 0;		// base 0 deg
  z = 23;		// 

  Serial.println("----------------------------------------");
  kinematics_calculation(a,b,x,y,z);
  servo1_angle = delta;
  servo2_angle = 180-(theta+beta);
  servo3_angle = 180-gamma;
  
  if (servo3_angle>=170){
    servo3_angle = 170;
  }
  if (servo2_angle>=140){
    servo2_angle = 140;
  }
  // servo1_angle = delta;
  // servo2_angle = theta+beta+51;
  // servo3_angle = 180-gamma;

  // servo1_angle = 90;
  // servo2_angle = 90;
  // servo3_angle = 0;

  // servo_test();
  // testing();

  // Applying Invese Kinematics
  move_servo();
  output();
}



 