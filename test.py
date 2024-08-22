import cv2
import cv2.aruco as aruco
from picamera2 import Picamera2, Preview

piCam2 = Picamera2()
piCam2.preview_configuration.main.size=(1280, 720)
piCam2.preview_configuration.main.format ="RGB888"
piCam2.preview_configuration.align()
piCam2.configure("preview")
piCam2.start()

# aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
# parameters = aruco.DetectorParameters_create()
dictionary = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters()
detector = aruco.ArucoDetector(dictionary, parameters)

# markerCiorners, markerIds, rejectedCandidates = detector.detectMarkers(frame)

while True:
    frame = piCam2.capture_array()
    corners, ids, rejectedCandidates = detector.detectMarkers(frame)

    print(ids)
    
    cv2.imshow("piCam", frame)
    if cv2.waitKey(1) == ord('q'):
        break
cv2.destroyAllWindows()
