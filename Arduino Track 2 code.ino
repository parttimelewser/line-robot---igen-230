int enR = 8; // Right Motor 
int in1 = 7; 
int in2 = 6;
int in3 = 5; // Left Motor 
int in4 = 4; 
int enL = 3; 

int thValue = 31;
int th1 = thValue; //Threshold Values
int th2 = thValue; 
int th3 = thValue; 
int th4 = thValue;
int th5 = thValue;

void setup(){ // Set all the motor control pins to outputs 
pinMode(enR, OUTPUT); 
pinMode(enL, OUTPUT); 
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT); 
pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT); 
Serial.begin(9600); 
}

void Rstop(){ // stop right motor 
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW); 
} 
void Lstop(){ // stop left motor 
digitalWrite(in3, LOW); 
digitalWrite(in4, LOW); 
} 
void Rf(){ // Right motor forwards 
digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH); 
} 
void Rb(){ // Right motor backwards 
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 
} 
void Lf(){ // Left motor forwards 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
} 
void Lb(){ // Left motor backwards 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
} 
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
  
void loop(){ 

  int rSpeed = 150; 
  int lSpeed = 150; 
  analogWrite(enR, rSpeed);     // Set speed to 200 out of possible range 0~255 
  analogWrite(enL, lSpeed);     // Set speed to 200 out of possible range 0~255 

  int val1=analogRead(A1);//A1 input reading, rightmost
  int val2=analogRead(A2);//A2 input reading
  int val3=analogRead(A3);//A3 input reading
  int val4=analogRead(A4);//A4 input reading
  int val5=analogRead(A5);//A4 input reading, leftmost

  int x = 10;
  int y = 80;

  int z = 0; //counter increases by 1 when you see BBBBB

  if(val5<th5 && val4<th4 && val3>th3 && val2<th2 && val1<th1){//WWBWW
  Rf();
  Lf();
  delay(x);
  Rstop();
  Lstop();
  delay(x);
  } 

//***********************************************************************************

  else if(val5>th5 && val4<th4 && val3<th3 && val2<th2 && val1<th1){//BWWWW
  Rf();
  Lstop();
  delay(x);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5<th5 && val4>th4 && val3<th3 && val2<th2 && val1<th1){//WBWWW
  Rf();
  Lstop();
  delay(x);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5>th5 && val4<th4 && val3>th3 && val2<th2 && val1<th1){//BWBWW
  Lb();
  delay(y);
  Rf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5>th5 && val4>th4 && val3<th3 && val2<th2 && val1<th1){//BBWWW
  Lb();
  delay(y);
  Rf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5>th5 && val4>th4 && val3>th3 && val2<th2 && val1<th1){//BBBWW
  Lb();
  delay(y);
  Rf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5>th5 && val4>th4 && val3>th3 && val2>th2 && val1<th1){//BBBBW
  Lb();
  delay(y);
  Rf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

//****************************************************************************************

  else if(val5<th5 && val4<th4 && val3<th3 && val2<th2 && val1>th1){//WWWWB
  Rstop();
  Lf();
  delay(y);
  Rstop();
  Lstop();
  delay(y);
  }

  else if(val5<th5 && val4<th4 && val3<th3 && val2>th2 && val1<th1){//WWWBW
  Rstop();
  Lf();
  delay(y);
  Rstop();
  Lstop();
  delay(y);
  }

  else if(val5<th5 && val4<th4 && val3>th3 && val2<th2 && val1>th1){//WWBWB
  Rb();
  delay(y);
  Lf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5<th5 && val4<th4 && val3<th3 && val2>th2 && val1>th1){//WWWBB
  Rb();
  delay(y);
  Lf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5<th5 && val4<th4 && val3>th3 && val2>th2 && val1>th1){//WWBBB
  Rb();
  delay(y);
  Lf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

  else if(val5<th5 && val4>th4 && val3>th3 && val2>th2 && val1>th1){//WBBBB
  Rb();
  delay(y);
  Lf();
  delay(y);
  Rstop();
  Lstop();
  delay(x);
  }

//**********************************************************

  else if(val5>th5 && val4>th4 && val3>th3 && val2>th2 && val1>th1){//BBBBB
  Rf();
  Lf();
  delay(x);
  Rstop();
  Lstop();
  delay(x);
  }

  else{//anything else
  Rf();
  Lf();
  delay(x);
  Rstop();
  Lstop();
  delay(x);
  }

}


