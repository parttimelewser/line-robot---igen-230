// Right Motor
int enR = 8; // Right Motor Speed
int in1 = 7; 
int in2 = 6;

// Left Motor
int in3 = 5;
int in4 = 4; 
int enL = 3; // Left Motor Speed

// Threshold values for IR sensors 1-5
int th1 = 55; 
int th2 = 55; 
int th3 = 55; 
int th4 = 55;
int th5 = 55;

// Set all the motor control pins to outputs
void setup(){  
  pinMode(enR, OUTPUT); 
  pinMode(enL, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  Serial.begin(9600);  // Begin serial monitoring
}

// Stop right motor
void Rstop(){  
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW); 
} 

// Stop left motor 
void Lstop(){ 
digitalWrite(in3, LOW); 
digitalWrite(in4, LOW); 
} 

// Right motor forwards
void Rf(){  
digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH); 
} 

// Right motor backwards
void Rb(){  
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 
} 

// Left motor forwards
void Lf(){  
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
} 

// Left motor backwards
void Lb(){ 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
} 

// Function to print ADC values of IR sensors in serial monitor
void info(){ 
Serial.print("     sOne = "); 
Serial.println(analogRead(A1));
Serial.print("     sTwo = "); 
Serial.println(analogRead(A2)); 
Serial.print("     sThree = "); 
Serial.println(analogRead(A3)); 
Serial.print("     sFour = "); 
Serial.println(analogRead(A4));
Serial.print("     sFive = "); 
Serial.println(analogRead(A5)); 
Serial.print("      "); 
Serial.println("      "); 
}
  
// Main loop
void loop(){ 

  int rSpeed = 150;   // Variable for right motor speed
  int lSpeed = 150;   // Variable for left motor speed
  analogWrite(enR, rSpeed);     // Set speed out of possible range 0~255 
  analogWrite(enL, lSpeed);     // Set speed out of possible range 0~255 

  int val1=analogRead(A1);    // A1 input reading, rightmost
  int val2=analogRead(A2);    // A2 input reading
  int val3=analogRead(A3);    // A3 input reading
  int val4=analogRead(A4);    // A4 input reading
  int val5=analogRead(A5);    // A4 input reading, leftmost

  // The following variables represent delay times (ms), the idea was that since the motors had different outputs,
  // the robot would turn left and right in varying degrees (ie. it would turn right more than left). To account
  // for this, we attempted to add delays in the functions to match the amount turned in both directions. For example,
  // if the robot turns more right then left, then we would increase the delay when turning left to allow the robot
  // more 'time' to turn left. However, this ended up not being used, as the problem resolved itself.
  int x = 4;    // Variable for increasing time of turning left
  int y = 4;    // Variable for increasing time of turning right

  // We use the following convention regarding the position of our sensors:
  // 'B' means detecting black, and 'W' means detecting white
  // Outer Left     Left      Middle      Right     Outer Right

  // Checks if Robot is centered, or in other words, if middle sensor is detecting black (WWBWW)
  if(val5<th5 && val4<th4 && val3>th3 && val2<th2 && val1<th1){
    // Runs both wheels forward
    Rf();
    Lf();
    delay(x);
    // Stops both wheels
    Rstop();
    Lstop();
    delay(x);
  } 

//***********************************************************************************
  // The following else-if statements account for if the robot is to the right of the black line

  // Checks if outer left sensor is detecting black (BWWWW)
  else if(val5>th5 && val4<th4 && val3<th3 && val2<th2 && val1<th1){
    // Run the right wheel but stop the left
    Rf();
    Lstop();
    delay(x);
    // Stop both wheels
    Rstop();
    Lstop();
    delay(x);
  }

  // Checks if left sensor is detecting black (WBWWW)
  else if(val5<th5 && val4>th4 && val3<th3 && val2<th2 && val1<th1){
    Rf();
    Lstop();
    delay(x);
    Rstop();
    Lstop();
    delay(x);
  }

  // Checks if outer left and left sensor is detecting black (BBWWW)
  else if(val5>th5 && val4>th4 && val3<th3 && val2<th2 && val1<th1){
    Rf();
    Lstop();
    delay(x);
    Rstop();
    Lstop();
    delay(x);
  }

  // Checks if outer left, left, and middle sensor is detecting black (BBBWW)
  else if(val5>th5 && val4>th4 && val3>th3 && val2<th2 && val1<th1){
    Rf();
    Lstop();
    delay(x);
    Rstop();
    Lstop();
    delay(x);
  }

  // Checks if outer left, left, middle, and right sensor is detecting black (BBBWW)
  else if(val5>th5 && val4>th4 && val3>th3 && val2>th2 && val1<th1){//BBBBW
    Rf();
    Lstop();
    delay(x);
    Rstop();
    Lstop();
    delay(x);
  }

//****************************************************************************************
  // The following else-if statements account for if the robot is to the left of the black line

  // Checks if outer right sensor is detecting black (WWWWB)
  else if(val5<th5 && val4<th4 && val3<th3 && val2<th2 && val1>th1){
    // Run the left wheel but stop the right
    Rstop();
    Lf();
    delay(y);
    // Stop both wheels
    Rstop();
    Lstop();
    delay(y);
  }

  // Checks if right sensor is detecting black (WWWBW)
  else if(val5<th5 && val4<th4 && val3<th3 && val2>th2 && val1<th1){
    Rstop();
    Lf();
    delay(y);
    Rstop();
    Lstop();
    delay(y);
  }

  // Checks if outer right and right sensor is detecting black (WWWBB)
  else if(val5<th5 && val4<th4 && val3<th3 && val2>th2 && val1>th1){
    Rstop();
    Lf();
    delay(y);
    Rstop();
    Lstop();
    delay(y);
  }

  // Checks if outer right, right and middle sensor is detecting black (WWBBB)
  else if(val5<th5 && val4<th4 && val3>th3 && val2>th2 && val1>th1){
    Rstop();
    Lf();
    delay(y);
    Rstop();
    Lstop();
    delay(y);
  }

  // Checks if outer right, right, middle and left sensor is detecting black (WBBBB)
  else if(val5<th5 && val4>th4 && val3>th3 && val2>th2 && val1>th1){
    Rstop();
    Lf();
    delay(y);
    Rstop();
    Lstop();
    delay(y);
  }

  // Robot goes forward if anything else
  else{
    // Run both wheels forward
    Rf();
    Lf();
    delay(y);
    // Stop both wheels
    Rstop();
    Lstop();
    delay(y);
  }

}
