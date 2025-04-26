const int numRows = 16;
const int numCols = 16;

const int delay_clr = 10;
const int delay_clc = 50;

const int colIdx[16] = {1, 3, 5, 7, 9, 11, 13, 15, 14, 12, 10, 8, 6, 4, 2, 0};

// 압력 데이터 저장 배열
int pressureData[numRows][numCols * 2] = {
  {0,},
};

// 핀 정의
const int clrPin = 5;     // 공통 CLR 핀
const int clkPin = 6;     // 공통 CLK 핀
const int sigPin1 = A0;    // 센서 출력 입력 핀
const int sigPin2 = A1;

void setFSRgpio(){
  // 핀 모드 설정
  pinMode(clrPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
}

void resetFSRcounter(){
  // 초기화: 클리어 한번만 수행
  digitalWrite(clrPin, LOW);
  delayMicroseconds(delay_clr);
  digitalWrite(clrPin, HIGH);
  delayMicroseconds(delay_clr);
  digitalWrite(clkPin, LOW);
}

void readPressureData(){
  // 카운터를 다시 0으로 초기화
  digitalWrite(clrPin, HIGH);
  delayMicroseconds(delay_clr);
  digitalWrite(clrPin, LOW);

  // 열 루프 (MUX 쪽 출력 0~3)
  for (int col = 0; col < numCols; col++) {
    // 행 루프 (DEMUX 쪽 출력 4~7)
    for (int row = 0; row < numRows; row++) {
      // 센서값 읽기
      int sensorValue1 = 1023 - analogRead(sigPin1);
      pressureData[colIdx[col]][row] = sensorValue1;
      int sensorValue2 = 1023 - analogRead(sigPin2);
      pressureData[colIdx[col]][row + numCols] = sensorValue2;

      // CLK 펄스 (행 증가)
      digitalWrite(clkPin, HIGH);
      delayMicroseconds(delay_clc);
      digitalWrite(clkPin, LOW);
      delayMicroseconds(delay_clc);
    }
  }
}

void sendJsonStart(){
  Serial.println("{");
}

void sendJsonEnd(){
  Serial.println("}");  // 전체 JSON 닫기
  Serial.println("END");  // JSON 한 세트의 끝 표시
}

void sendPressureDataAsJson() {
  Serial.println("\"FSR\": {");

  for (int row = 0; row < numRows; row++) {
    Serial.print("\"row");
    Serial.print(row);
    Serial.print("\": [");

    for (int col = 0; col < numCols * 2; col++) {
      Serial.print(pressureData[row][col]);
      if (col < numCols * 2 - 1) Serial.print(",");
    }

    Serial.print("]");
    if (row < numRows - 1) Serial.println(",");  // 마지막 줄엔 쉼표 없음
    else Serial.println("");
  }

  Serial.println("}");  // FSR 닫기
}

void setup() {
  Serial.begin(115200);
  setFSRgpio();
  resetFSRcounter();
}

void loop() {
  readPressureData();
  sendJsonStart();
  sendPressureDataAsJson();
  sendJsonEnd();
  delay(200);
}