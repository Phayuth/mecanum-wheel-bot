// define motor pin
#define topleft_Rpwm_pin 5
#define topleft_Lpwm_pin 4
#define topright_Rpwm_pin 7
#define topright_Lpwm_pin 6
#define downleft_Rpwm_pin 11
#define downleft_Lpwm_pin 10
#define downright_Rpwm_pin 8
#define downright_Lpwm_pin 9

// preassign variable
int topleft_pwm;
int topright_pwm;
int downleft_pwm;
int downright_pwm;

// mobile robot parameter
float Vx;      // linear velocity x
float Vy;      // linear velocity y
float omega;   // angular velocity
const float l_1 = 0.5;  // distance from wheel axis X
const float l_2 = 0.5;  // distance from wheel axis Y
const float R = 0.2;    // robot wheel radius in m

float topleft_speed;
float topright_speed;
float downleft_speed;
float downright_speed;

void setup() {
  // set pins motor output
  pinMode(topleft_Rpwm_pin, OUTPUT);
  pinMode(topleft_Lpwm_pin, OUTPUT);
  pinMode(topright_Rpwm_pin, OUTPUT);
  pinMode(topright_Lpwm_pin, OUTPUT);
  pinMode(downleft_Rpwm_pin, OUTPUT);
  pinMode(downleft_Lpwm_pin, OUTPUT);
  pinMode(downright_Rpwm_pin, OUTPUT);
  pinMode(downright_Lpwm_pin, OUTPUT);
}

void loop() {
  // get Vx Vy and omega from controller
  Vx = 0.2;
  Vy = 0.2;
  omega = 0.01;

  // convert V and omega to each wheel speed
  topleft_speed = (1 / R) * (Vx + Vy - (l_1 + l_2) * omega);
  topright_speed = (1 / R) * (Vx - Vy + (l_1 + l_2) * omega);
  downleft_speed = (1 / R) * (Vx - Vy - (l_1 + l_2) * omega);
  downright_speed = (1 / R) * (Vx + Vy + (l_1 + l_2) * omega);

  // convert each wheel speed to pwm value, y=Ax+b, A=0.22,b=0.1
  topleft_pwm = 1 * topleft_speed + 0;
  topright_pwm = 1 * topright_speed + 0;
  downleft_pwm = 1 * downleft_speed + 0;
  downright_pwm = 1 * downright_speed + 0;

  // limit pwm
  if (topleft_pwm < -255) {
    topleft_pwm = -255;
  }
  if (topleft_pwm > 255) {
    topleft_pwm = 255;
  }
  if (topright_pwm < -255) {
    topright_pwm = -255;
  }
  if (topright_pwm > 255) {
    topright_pwm = 255;
  }
  if (downleft_pwm < -255) {
    downleft_pwm = -255;
  }
  if (downleft_pwm > 255) {
    downleft_pwm = 255;
  }
  if (downright_pwm < -255) {
    downright_pwm = -255;
  }
  if (downright_pwm > 255) {
    downright_pwm = 255;
  }

  // write pwm to pin
  if ( topleft_pwm > 0 && topright_pwm > 0 && downleft_pwm > 0 && downright_pwm > 0) {
    // all forward 1
    analogWrite(topleft_Rpwm_pin, topleft_pwm);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm < 0 && topright_pwm < 0 && downleft_pwm < 0 && downright_pwm < 0) {
    // all reverse 2
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, downleft_pwm * -1);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }


  else if ( topleft_pwm < 0 && topright_pwm > 0 && downleft_pwm > 0 && downright_pwm > 0) {
    // topleft reverse 3
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm > 0 && topright_pwm < 0 && downleft_pwm > 0 && downright_pwm > 0) {
    // topright reverse 4
    analogWrite(topleft_Rpwm_pin, topleft_pwm);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm > 0 && topright_pwm > 0 && downleft_pwm < 0 && downright_pwm > 0) {
    //downleft reverse 5
    analogWrite(topleft_Rpwm_pin, topleft_pwm);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, downleft_pwm * -1);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm > 0 && topright_pwm > 0 && downleft_pwm > 0 && downright_pwm < 0) {
    //downright reverse 6
    analogWrite(topleft_Rpwm_pin, topleft_pwm);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }


  else if ( topleft_pwm < 0 && topright_pwm < 0 && downleft_pwm > 0 && downright_pwm > 0) {
    //topleft topright reverse 7
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm < 0 && topright_pwm > 0 && downleft_pwm < 0 && downright_pwm > 0) {
    //topleft downleft reverse 8
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, downleft_pwm * -1);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm < 0 && topright_pwm > 0 && downleft_pwm > 0 && downright_pwm < 0) {
    //topleft downright reverse 9
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }
  else if ( topleft_pwm > 0 && topright_pwm < 0 && downleft_pwm < 0 && downright_pwm > 0) {
    //topleft downright reverse 10
    analogWrite(topleft_Rpwm_pin, topleft_pwm);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, downleft_pwm * -1);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm > 0 && topright_pwm < 0 && downleft_pwm > 0 && downright_pwm < 0) {
    //topright downright reverse 11
    analogWrite(topleft_Rpwm_pin, topleft_pwm);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }
  else if ( topleft_pwm > 0 && topright_pwm > 0 && downleft_pwm < 0 && downright_pwm < 0) {
    //downleft downright reverse 12
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }
  else if ( topleft_pwm < 0 && topright_pwm < 0 && downleft_pwm < 0 && downright_pwm > 0) {
    //topleft topright downleft reverse 13
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, downleft_pwm * -1);
    analogWrite(downright_Rpwm_pin, downright_pwm);
    analogWrite(downright_Lpwm_pin, 0);
  }
  else if ( topleft_pwm < 0 && topright_pwm > 0 && downleft_pwm < 0 && downright_pwm < 0) {
    //topleft downleft downright reverse 14
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, topright_pwm);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, downleft_pwm * -1);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }
  else if ( topleft_pwm < 0 && topright_pwm < 0 && downleft_pwm > 0 && downright_pwm < 0) {
    //topleft topright downright reverse 15
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, topleft_pwm * -1);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, downleft_pwm);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }
  else if ( topleft_pwm > 0 && topright_pwm < 0 && downleft_pwm < 0 && downright_pwm < 0) {
    //topright downleft downright reverse 16
    analogWrite(topleft_Rpwm_pin, topleft_pwm);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, topright_pwm * -1);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, downleft_pwm * -1);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, downright_pwm * -1);
  }
  else {
    // neutral
    analogWrite(topleft_Rpwm_pin, 0);
    analogWrite(topleft_Lpwm_pin, 0);
    analogWrite(topright_Rpwm_pin, 0);
    analogWrite(topright_Lpwm_pin, 0);
    analogWrite(downleft_Rpwm_pin, 0);
    analogWrite(downleft_Lpwm_pin, 0);
    analogWrite(downright_Rpwm_pin, 0);
    analogWrite(downright_Lpwm_pin, 0);
  }
}
