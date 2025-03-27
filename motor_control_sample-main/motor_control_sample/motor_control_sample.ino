// 모터 핀 정의
const int motor1_in1 = 2;
const int motor1_in2 = 3;
const int motor1_pwm = 10;

const int motor2_in1 = 4;
const int motor2_in2 = 5;
const int motor2_pwm = 11;

const int alwaysLow1 = 8;
const int alwaysLow2 = 9;
const int alwaysHigh1 = 12;
const int alwaysHigh2 = 13;

// 초기 설정
void setup() {
  
  // 모터 제어 핀을 출력 모드로 설정
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor1_pwm, OUTPUT);
  
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor2_pwm, OUTPUT);

  // 항상 LOW와 HIGH로 유지할 핀 설정
  pinMode(alwaysLow1, OUTPUT);
  pinMode(alwaysLow2, OUTPUT);
  pinMode(alwaysHigh1, OUTPUT);
  pinMode(alwaysHigh2, OUTPUT);
  
  digitalWrite(alwaysLow1, LOW);
  digitalWrite(alwaysLow2, LOW);
  digitalWrite(alwaysHigh1, HIGH);
  digitalWrite(alwaysHigh2, HIGH);
}

// 모터 제어 함수
void controlMotor(int in1, int in2, int pwm, int speed, bool direction) {
  digitalWrite(in1, direction);     // 방향 설정
  digitalWrite(in2, !direction);    // 반대 방향 설정
  analogWrite(pwm, speed);          // 속도 설정
}

// 메인 루프
void loop() {
  // 모터 1 정방향 회전
  controlMotor(motor1_in1, motor1_in2, motor1_pwm, 255, true);
  delay(1000);  // 1초 동안 회전
  
  // 모터 1 역방향 회전
  controlMotor(motor1_in1, motor1_in2, motor1_pwm, 255, false);
  delay(1000);  // 1초 동안 회전
  
  // 모터 1 멈춤
  controlMotor(motor1_in1, motor1_in2, motor1_pwm, 0, true);
  delay(1000);  // 1초 동안 멈춤
  
  // 모터 2 정방향 회전
  controlMotor(motor2_in1, motor2_in2, motor2_pwm, 255, true);
  delay(1000);  // 1초 동안 회전
  
  // 모터 2 역방향 회전
  controlMotor(motor2_in1, motor2_in2, motor2_pwm, 255, false);
  delay(1000);  // 1초 동안 회전
  
  // 모터 2 멈춤
  controlMotor(motor2_in1, motor2_in2, motor2_pwm, 0, true);
  delay(1000);  // 1초 동안 멈춤
}
