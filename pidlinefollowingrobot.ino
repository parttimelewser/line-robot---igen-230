#include <stdlib.h>
#include <NewPing.h>


//assign pins 
#define ENA 17
#define ENB 16
#define IN1 21
#define IN2 19
#define IN3 18
#define IN4 5
#define TRIGGER 12
#define ECHO 13
#define MAX_DIST 400

// configured     1 2 3 4 5 
//                    6
#define SENS1 2
#define SENS2 4
#define SENS3 14
#define SENS4 15
#define SENS5 26
//#define SENS6 25

int sensarray[5] = {SENS1, SENS2, SENS3, SENS4, SENS5};


//defining values used in calculation of PID control -- "weights"
float Kp = 0.3;
float Ki = 0;
float Kd = 7;

//defining variables used in calculations later 
float Pvalue;
float Ivalue;
float Dvalue;

int position;
int P, D, I, previousError, PIDvalue, error, distance;
int lsp, rsp;

//defining base speed of each motor -- speed it will run if on a straight line
int lbasespd = 160;
int rbasespd = 160;

long desiredpos;

//defining array to hold values of 5 sensors in a line -- after mapping 
long sensorValues[5];

//defining array to hold maximum/minimum sensors for configuration
long minimum[5];
long maximum[5];


//array holding values of sensors -- before mapping 
long reading[5];

//holds previous reading of sensors for comparison 
long old[5];

//defining where desired position is (changes depending on lighting)

//defining variables to allow speed control of motors -- to us ledcwrite function
const int freq = 30000;
const int res = 8; 
const int pwm_1 = 0;
const int pwm_2 = 1;
int dutyCycle = 255; 

void setup() {
  // defining pin mode / assigning ledcwrite channels 
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  ledcAttachChannel(ENA,freq,res,pwm_1);
  ledcAttachChannel(ENB,freq,res,pwm_2);

  //opening the serial monitor (used for testing)
  Serial.begin(115200);

  delay(1000);
  //run configuration function and print the max/min values of each sensor and reading for desired position
  configuring();

    for (int i = 0; i<=4 ; i++){
      Serial.print(maximum[i]);
      Serial.print("  ");
      Serial.print(minimum[i]);
      Serial.print("  ");
    }

    Serial.print(desiredpos);
    Serial.println(); 

    delay(5000);

}

void loop() {
    //run line following function 
    PID_Linefollow();
    }



void PID_Linefollow(){
  //gets the position and how much it is off from desired position
    position = getposition();
    error = desiredpos - position;
  //calculating PID value to predict change in line placement and to adjust the motor speed accordingly 
    P = error;
    I = I + error;
    D = error - previousError;
    
    Pvalue = Kp*P;
    Ivalue = (Ki)*I;
    Dvalue = (Kd)*D; 

    float PIDvalue = Pvalue + Ivalue + Dvalue;
    previousError = error;

    //changes speed of motor proportional to the positioning of the robot using PID algorithm 
    lsp = lbasespd - PIDvalue;
    rsp = rbasespd + PIDvalue;

  //checks the position and if it is on the sensors at the end, make sharp left/right turn, otherwise limits the speed to between 120 and 200 (prevents stalling or going too fast to read accurately)
    if (position <=3200 && position >=100){
    
      if (lsp > 200) {
        lsp = 200;
      }
      if (lsp < 120) {
        lsp = 120;
      }

      if (rsp > 200) {
        rsp = 200;
      }

      if (rsp < 120) {
        rsp = 120;
      }
    }

    if (position > 300){
      lsp = 170;
      rsp = 0;
      // delay(250);
      // rsp = 0;
    }

    if (position < 100){
      rsp = 170;
      lsp = 0;
      // delay(250);
      // rsp = 0;
    }
//writes values to motors to change speed accordingly 
    motor_drive(lsp,rsp);

    // Serial.print(lsp);
    // Serial.print("  ");
    // Serial.println(rsp);
  }

void motor_drive(int left, int right){
  
  if(right>0)
  {
    //tells right motor to go forward if calculated right motor speed is positive
    ledcWriteChannel(pwm_1,abs(right));
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW); 

  }
  else 
  {
    //tells right motor to go backward if calculated right motor speed is negative
    ledcWriteChannel(pwm_1,abs(right)); 
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH); 
  }
  
 
  if(left>0)
  {
    //tells left motor to go forward if calculated left motor speed is positive
    ledcWriteChannel(pwm_2,abs(left));
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW); 
  }
  else 
  {
    //tells left motor to go backward if calculated left motor speed is negative
    ledcWriteChannel(pwm_2,abs(left));
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH); 
  }
}

//function to take the weighted average (position) of the array to indicate where the black line is -- sensor position lines up with the array 
long getposition(){
  long position = 0;
  long sum = 0;
  long sum_weight = 0; 

  for (int i = 0; i<=4; i++){

    reading[i] = analogRead(sensarray[i]);
  //rewrites any values outside of the max/min to be the max or min respectively 
    if (reading[i] > maximum[i]){
      reading[i] = maximum[i];
    }

    if (reading[i] < minimum[i]){
      reading[i] = minimum[i];
    }

  //sets each entry of an array as a sensor reading, in the same order as on the bracket, mapped out onto the same scale  

    sensorValues[i] = map (reading[i], minimum[i], maximum[i], 1,500);

    sum = sum + sensorValues[i];
    sum_weight = sum_weight + (sensorValues[i]*i*100);



  }
  
  position = sum_weight/sum;

  return position; 

}

void configuring(){
//takes 80 readings at 100ms intervals and saves the minimum values 
    Serial.println("configuring minimum");

    old[0] = analogRead(SENS1);
    old[1] = analogRead(SENS2);
    old[2] = analogRead(SENS3);
    old[3]= analogRead(SENS4);
    old[4] = analogRead(SENS5);

  for (int a = 0; a<=80; a++){
    delay(100);

    for (int i = 0; i <=4; i++) {

    reading[i] = analogRead(sensarray[i]);

    minimum[i] = min(reading[i], old[i]);
     
    old[i] = reading[i];

    }
  }
//takes 80 readings at 100ms intervals and saves the maximum values
   Serial.println("configuring maximum"); 

  for (int b = 0; b<=80; b++){
    delay(100);

    for (int i = 0; i <=4; i++) {

    reading[i] = analogRead(sensarray[i]);

    maximum[i] = max(reading[i], old[i]);
     
    old[i] = reading[i];

    }
  }

   Serial.println("move to desired position");

   delay(5000);

   Serial.println("configuring desired position");
//takes the mean of 50 readings at 100ms intervals of the position to save as the desired position
   int sumdesiredpos = 0; 

   for (int c = 0; c<50;c++){
    sumdesiredpos = sumdesiredpos + getposition();
    
    delay(100);
  }

  desiredpos = sumdesiredpos/50;

}