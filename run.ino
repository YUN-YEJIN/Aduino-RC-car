
/*
   Ryken Santillan
   05/06/2022
   Code for Line-Tracing Robot 
   Project Members: George Chen, Jimmie So
*/

//-----Motor Connections

// Motor A connections --> 방향제어
int moterA1 = 9;   
int moterA2 = 10;
// Motor B connections
int moterB1 = 5;   
int moterB2 = 6;

//-----IR Connections
int leftSensorPin = A0;
int rightSensorPin = A1;

int leftSensorValue = 0;
int rightSensorValue = 0;

//range for black tape
int blackLeft = 400; 
int blackRight = 400;

//-----Purpose: Initialize necessary components and their pins-----//
void setup() {
  //Set all motor control pins to output
  Serial.begin(9600);
   // Turn off motors - Initial state
  pinMode(moterA1, OUTPUT);
  pinMode(moterA2, OUTPUT);
  pinMode(moterB1, OUTPUT);
  pinMode(moterB2, OUTPUT);

   digitalWrite(moterA1, LOW);
  digitalWrite(moterA2, LOW);
  digitalWrite(moterB1, LOW);
  digitalWrite(moterB2, LOW);
}

//Purpose: Infinite loop, keep robot in perpetual motion
void loop() {
  detect(); //function to track LDR analog values
  movement(); //function for movement
  Serial.print("L: "); Serial.print(leftSensorValue);
  Serial.print(" | R: "); Serial.println(rightSensorValue);

}

//Purpose: Tracks IR analog values and stores them into variables
void detect() { 
  leftSensorValue = analogRead(A0);
  rightSensorValue = analogRead(A1);
}

/*Purpose: Moves the robot depending on what IRs detect
1.) Middle = Black, Right = White: Robot moves forward
2.) Middle = Black, Right = Black; Robot turns right until only middle is black
3.) Middle = White, Right = White, Robot turns left until middle reads black
*/

void movement() { 
  if (leftSensorValue <= blackLeft && rightSensorValue <= blackRight) {
    // move straight
    digitalWrite(moterA1,HIGH); //RIGHT MOTOR FORWARD ON
    digitalWrite(moterA2,LOW); //RIGHT MOTOR BACKWARD OFF
    digitalWrite(moterB1,HIGH);  //LEFT MOTOR FORWARD ON
    digitalWrite(moterB2,LOW);  //LEFT MOTOR BACKWARD OFF
  }
  else if (leftSensorValue > blackLeft && rightSensorValue <= blackRight) {
    //turn RIGHT
    digitalWrite(moterA1,LOW); //RIGHT MOTOR FORWARD OFF
    digitalWrite(moterA2,HIGH); //RIGHT MOTOR BACKWARD ON
    digitalWrite(moterB1,HIGH);  //LEFT MOTOR FORWARD ON
    digitalWrite(moterB2,LOW);  //LEFT MOTOR BACKWARD OFF
  }
   else if(leftSensorValue <= blackLeft && rightSensorValue > blackRight) {
    //turn Left
    digitalWrite(moterA1,HIGH); //RIGHT MOTOR FORWARD OFF
    digitalWrite(moterA2,LOW); //RIGHT MOTOR BACKWARD ON
    digitalWrite(moterB1,LOW);  //LEFT MOTOR FORWARD ON
    digitalWrite(moterB2,HIGH);  //LEFT MOTOR BACKWARD OFF
  }
  else {
    // move backward
    digitalWrite(moterA1,LOW); //RIGHT MOTOR FORWARD OFF
    digitalWrite(moterA2,HIGH); //RIGHT MOTOR BACKWARD ON
    digitalWrite(moterB1,LOW);  //LEFT MOTOR FORWARD OFF
    digitalWrite(moterB2,HIGH);  //LEFT MOTOR BACKWARD ON
  }
}
