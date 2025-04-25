// 16x16 매트릭스 압력 센서 핀 정의
const int numRows = 16;
const int numCols = 16;

// 행 핀 정의 (디지털 핀 22~37 및 38~53)
int rowPins1[numRows] = {38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53}; // 압력 센서 2 행 핀
int rowPins2[numRows] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37}; // 압력 센서 1 행 핀


// 압력 데이터 배열
int pressureData1[numRows][numCols]; // 압력 센서 1 데이터
int pressureData2[numRows][numCols]; // 압력 센서 2 데이터

// 멀티플렉서 1 핀 정의
const int sigPin1 = A0;  // SIG 핀
const int s0Pin1 = 4;    // S0 핀
const int s1Pin1 = 5;    // S1 핀
const int s2Pin1 = 6;    // S2 핀
const int s3Pin1 = 7;    // S3 핀

// 멀티플렉서 2 핀 정의
const int sigPin2 = A1;  // SIG 핀
const int s0Pin2 = 8;    // S0 핀
const int s1Pin2 = 9;    // S1 핀
const int s2Pin2 = 10;   // S2 핀
const int s3Pin2 = 11;   // S3 핀

void setup() {
  Serial.begin(115200);

  // 행 핀을 출력 모드로 설정 (압력 센서 1)
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins1[i], OUTPUT);
    digitalWrite(rowPins1[i], LOW); // 기본적으로 LOW로 설정
  }

  // 행 핀을 출력 모드로 설정 (압력 센서 2)
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins2[i], OUTPUT);
    digitalWrite(rowPins2[i], LOW); // 기본적으로 LOW로 설정
  }

  // 멀티플렉서 선택 핀을 출력 모드로 설정
  pinMode(s0Pin1, OUTPUT);
  pinMode(s1Pin1, OUTPUT);
  pinMode(s2Pin1, OUTPUT);
  pinMode(s3Pin1, OUTPUT);

  pinMode(s0Pin2, OUTPUT);
  pinMode(s1Pin2, OUTPUT);
  pinMode(s2Pin2, OUTPUT);
  pinMode(s3Pin2, OUTPUT);
}

void loop() {
  // 첫 번째 압력 센서 데이터 읽기
  for (int row = 0; row < numRows; row++) {
    digitalWrite(rowPins1[row], HIGH); // 압력 센서 1의 현재 행 선택

    for (int col = 0; col < numCols; col++) {
      // 멀티플렉서 1의 선택 핀 설정
      digitalWrite(s0Pin1, col & 0x01);
      digitalWrite(s1Pin1, (col >> 1) & 0x01);
      digitalWrite(s2Pin1, (col >> 2) & 0x01);
      digitalWrite(s3Pin1, (col >> 3) & 0x01);
      
      // 아날로그 값 읽기
      int sensorValue = analogRead(sigPin1);
      // 압력 값을 직접 저장
      pressureData1[row][col] = sensorValue;
    }
    digitalWrite(rowPins1[row], LOW); // 행 선택 해제
  }

  // 두 번째 압력 센서 데이터 읽기
  for (int row = 0; row < numRows; row++) {
    digitalWrite(rowPins2[row], HIGH); // 압력 센서 2의 현재 행 선택

    for (int col = 0; col < numCols; col++) {
      // 멀티플렉서 2의 선택 핀 설정
      digitalWrite(s0Pin2, col & 0x01);
      digitalWrite(s1Pin2, (col >> 1) & 0x01);
      digitalWrite(s2Pin2, (col >> 2) & 0x01);
      digitalWrite(s3Pin2, (col >> 3) & 0x01);
      
      // 아날로그 값 읽기
      int sensorValue = analogRead(sigPin2);
      // 압력 값을 직접 저장
      pressureData2[row][col] = sensorValue;
    }
    digitalWrite(rowPins2[row], LOW); // 행 선택 해제
  }

  // 압력 데이터 출력
  Serial.println("Pressure Sensor 1 Data:");
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      Serial.print(pressureData1[row][col]);
      if (col < numCols - 1) Serial.print(","); // 열 사이에 , 삽입
    }
    Serial.println();
  }

  Serial.println("Pressure Sensor 2 Data:");
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      Serial.print(pressureData2[row][col]);
      if (col < numCols - 1) Serial.print(","); // 열 사이에 , 삽입
    }
    Serial.println();
  }
  
  Serial.println("END"); // 한 프레임의 끝을 표시
  delay(500);
}
