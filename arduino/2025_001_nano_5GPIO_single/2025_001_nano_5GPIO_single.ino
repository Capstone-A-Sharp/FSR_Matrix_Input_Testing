const int numRows = 16;
const int numCols = 16;
const int RnumRows = 10;
const int RnumCols = 10;

// 압력 데이터 저장 배열
int pressureData[numRows][numCols] = {0};

// 핀 정의
const int clrPinDemux = 5; // Demux CLR 핀
const int clrPinMux   = 4; // Mux CLR 핀
const int demuxClk = 6;    // Demux 카운터 CLK
const int muxClk   = 7;    // Mux 카운터 CLK
const int sigPin   = A0;   // 센서 출력 입력 핀

void setup() {
  Serial.begin(115200);

  // 핀 모드 설정
  pinMode(clrPinDemux, OUTPUT);
  pinMode(clrPinMux, OUTPUT);
  pinMode(demuxClk, OUTPUT);
  pinMode(muxClk, OUTPUT);

  // 전체 초기화
  digitalWrite(clrPinDemux, LOW);
  digitalWrite(clrPinMux, LOW);
  delayMicroseconds(10);
  digitalWrite(clrPinDemux, HIGH);
  digitalWrite(clrPinMux, HIGH);

  digitalWrite(demuxClk, LOW);
  digitalWrite(muxClk, LOW);
}

void loop() {
  // 두 카운터 모두 0으로 초기화
  digitalWrite(clrPinDemux, LOW);
  digitalWrite(clrPinMux, LOW);
  delayMicroseconds(10);
  digitalWrite(clrPinDemux, HIGH);
  digitalWrite(clrPinMux, HIGH);

  // 열 루프 (mux 측 제어)
  for (int col = 0; col < RnumCols; col++) {
    // 행 루프 (demux 측 제어)
    for (int row = 0; row < RnumRows; row++) {
      // 센서값 읽기
      int sensorValue = 1023 - analogRead(sigPin);
      pressureData[row][col] = sensorValue;

      // Demux CLK 펄스 (행 증가)
      digitalWrite(demuxClk, HIGH);
      delayMicroseconds(5);
      digitalWrite(demuxClk, LOW);
      delayMicroseconds(5);
    }

    // Mux CLR로 행 다시 0으로
    digitalWrite(clrPinDemux, LOW);
    delayMicroseconds(10);
    digitalWrite(clrPinDemux, HIGH);

    // Mux CLK 펄스 (열 증가)
    digitalWrite(muxClk, HIGH);
    delayMicroseconds(5);
    digitalWrite(muxClk, LOW);
    delayMicroseconds(5);
  }

  // 데이터 출력
  Serial.println("Pressure Sensor Data:");
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      Serial.print(pressureData[row][col]);
      if (col < numCols - 1) Serial.print(",");
    }
    Serial.println();
  }

  Serial.println("END");
  delay(500);
}
