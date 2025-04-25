const int numRows = 16;
const int numCols = 16;

const int colIdx[16] = {1, 3, 5, 7, 9, 11, 13, 15, 14, 12, 10, 8, 6, 4, 2, 0};

// 압력 데이터 저장 배열
int pressureData[numRows][numCols*2] = {0};

// 핀 정의
const int clrPin = 5;     // 공통 CLR 핀
const int clkPin = 6;     // 공통 CLK 핀
const int sigPin1 = A0;    // 센서 출력 입력 핀
const int sigPin2 = A1;

void setup() {
  Serial.begin(115200);

  // 핀 모드 설정
  pinMode(clrPin, OUTPUT);
  pinMode(clkPin, OUTPUT);

  // 초기화: 클리어 한번만 수행
  digitalWrite(clrPin, LOW);
  delayMicroseconds(10);
  digitalWrite(clrPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(clkPin, LOW);
}

void loop() {
  // 카운터를 다시 0으로 초기화
  digitalWrite(clrPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(clrPin, LOW);

  // 열 루프 (MUX 쪽 출력 0~3)
  for (int col = 0; col < numCols; col++) {
    // 행 루프 (DEMUX 쪽 출력 4~7)
    for (int row = 0; row < numRows; row++) {
      // 센서값 읽기
      int sensorValue1 = 1023 - analogRead(sigPin1);
      pressureData[colIdx[col]][row] = sensorValue1;
      int sensorValue2 = 1023 - analogRead(sigPin2);
      pressureData[colIdx[col]][row + numRows] = sensorValue2;

      // CLK 펄스 (행 증가)
      digitalWrite(clkPin, HIGH);
      delayMicroseconds(50);
      digitalWrite(clkPin, LOW);
      delayMicroseconds(50);
    }
  }

  // 압력 데이터 출력
  Serial.println("Pressure Sensor Data:");
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols * 2; col++) {
      Serial.print(pressureData[row][col]);
      if (col < numCols * 2 - 1) Serial.print(","); // 열 사이에 , 삽입
    }
    Serial.println();
  }
  
  Serial.println("END"); // 한 프레임의 끝을 표시
  delay(200);
}