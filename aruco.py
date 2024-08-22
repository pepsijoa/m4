import cv2
import cv2.aruco as aruco

# 카메라 캘리브레이션 및 로드 (카메라와 관련된 파라미터를 설정)
camera_matrix = ...  # 카메라 매트릭스
dist_coeffs = ...    # 왜곡 계수

# Aruco 마커 딕셔너리와 파라미터 설정
aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters_create()

# 비디오 캡처 또는 이미지 읽기
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # 마커 검출
    corners, ids, _ = aruco.detectMarkers(frame, aruco_dict, parameters=parameters)

    # 마커가 검출된 경우
    if ids is not None:
        aruco.drawDetectedMarkers(frame, corners, ids)

        # 검출된 마커와 번호 출력
        for i, marker_id in enumerate(ids.flatten()):
            print(f"Detected marker ID: {marker_id}")

    # 결과 이미지 표시
    cv2.imshow('Frame', frame)

    # 종료 조건
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
