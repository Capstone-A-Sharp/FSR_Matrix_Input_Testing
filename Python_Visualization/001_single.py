import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Arduino와 연결된 시리얼 포트 설정
ser = serial.Serial('/dev/cu.usbserial-A5069RR4', 115200)  # 포트를 'COM14'로 설정
numRows, numCols = 16, 16

# 시각화 설정
plt.style.use('dark_background')
fig, ax = plt.subplots()
# 'inferno' 색상 맵과 bilinear 보간을 사용해 더 부드럽고 명확하게 표현
img = ax.imshow(np.zeros((numRows, numCols)), cmap='inferno', interpolation='bilinear', vmin=0, vmax=100)
plt.colorbar(img, ax=ax, label="Pressure Intensity")

def update_data(*args):
    global ser
    pressure_matrix = np.zeros((numRows, numCols))
    row = 0

    # 데이터 읽기
    while row < numRows:
        line = ser.readline().decode().strip()
        if line == "END":
            break
        values = line.split(',')
        if len(values) == numCols:
            # 시리얼에서 읽은 데이터 출력
            print(f"Row {row}: {values}")
            pressure_matrix[row] = list(map(int, values))
            row += 1

    # 모든 행의 데이터가 준비된 경우에만 업데이트
    if row == numRows:
        img.set_data(pressure_matrix)
    return [img]

# 애니메이션으로 실시간 업데이트 설정
ani = animation.FuncAnimation(fig, update_data, interval=100, blit=False)  # 딜레이 100ms로 설정
plt.title("Real-Time Pressure Sensor Visualization (16x16)")
plt.show()