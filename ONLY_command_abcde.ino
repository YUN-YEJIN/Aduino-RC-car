/* 유의사항
1. A1,A2 의미하는 것: 전진 모터,후진 모터 
*/
#include <SoftwareSerial.h>

// 블루투스 연결 (TX: 8, RX: 7 로 예시)
#define BT_RX 8
#define BT_TX 7
SoftwareSerial bluetooth(BT_RX, BT_TX);

// 모터 A
int motorA1 = 9;
int motorA2 = 10;

// 모터 B
int motorB1 = 5;
int motorB2 = 6;

void setup() {
  // 모터 핀 출력 설정
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  // 시리얼 통신
  Serial.begin(9600);
  bluetooth.begin(9600);  // HC-05 기본 속도
  myRC.stop();

  Serial.println("Bluetooth 모터 제어 준비 완료");
}

void loop() {
  // Bluetooth(phone) → Serial(PC) ->Arduino   (we don't use in this code!!!!)
  if (bluetooth.available()) {
    char data = bluetooth.read();
    Serial.write(data);  // 시리얼 모니터에 출력

    controlMotor(data);  // 명령어 처리
  }

  // Serial -> Bluetooth(PC)-> Arduino
  if (Serial.available()) {
    char data = Serial.read();
    bluetooth.write(data);  // Bluetooth로도 전달
    controlMotor(data);
  }
}

void controlMotor(char cmd) {
  switch (cmd) {
    case 'a':  // 전진
      forward();
      break;
    case 'b':  // 후진
      backward();
      break;
    case 'c':  // 좌회전
      turnLeft();
      break;
    case 'd':  // 우회전
      turnRight();
      break;
    case 'e':  // 정지
      stopMotors();
      break;
  }
}

void forward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void backward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
