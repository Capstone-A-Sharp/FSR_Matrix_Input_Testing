import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import json

# Arduino와 연결된 시리얼 포트 설정
ser = serial.Serial('/dev/cu.usbserial-A5069RR4', 115200)  # 포트를 'COM14'로 설정
numRows, numCols = 16, 32

# 시각화 설정
plt.style.use('dark_background')
fig, ax = plt.subplots()
# 'inferno' 색상 맵과 bilinear 보간을 사용해 더 부드럽고 명확하게 표현
img = ax.imshow(np.zeros((numRows, numCols)), cmap='inferno', interpolation='bilinear', vmin=0, vmax=100)
plt.colorbar(img, ax=ax, label="Pressure Intensity")

def read_complete_json():
    json_lines = []
    while True:
        line = ser.readline().decode(errors='ignore').strip()
        if line == "END":
            break
        json_lines.append(line)
    return "\n".join(json_lines)

def update_data(*args):
    global ser
    pressure_matrix = np.zeros((numRows, numCols))

    try:
        json_str = read_complete_json()
        data = json.loads(json_str)

        fsr_data = data.get("FSR", {})
        for row in range(numRows):
            row_key = f"row{row}"
            if row_key in fsr_data and len(fsr_data[row_key]) == numCols:
                pressure_matrix[row] = fsr_data[row_key]
            else:
                print(f"{row_key} 누락 또는 길이 오류")

        img.set_data(pressure_matrix)
    except Exception as e:
        print("JSON 파싱 오류:", e)

    return [img]

# 애니메이션으로 실시간 업데이트 설정
ani = animation.FuncAnimation(fig, update_data, interval=100, blit=False)  # 딜레이 100ms로 설정
plt.title("Real-Time Pressure Sensor Visualization (16x16)")
plt.show()