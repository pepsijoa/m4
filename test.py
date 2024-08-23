import cv2
import cv2.aruco as aruco
from picamera2 import Picamera2, Preview
import time



def detect():
    piCam2 = Picamera2()
    piCam2.preview_configuration.main.size=(1280, 720)
    piCam2.preview_configuration.main.format ="RGB888"
    piCam2.preview_configuration.align()
    piCam2.configure("preview")
    piCam2.start()

    dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)
    parameters = aruco.DetectorParameters()
    detector = aruco.ArucoDetector(dictionary, parameters)


    while True:
        frame = piCam2.capture_array()
        corners, ids, rejectedCandidates = detector.detectMarkers(frame)

        if ids is not None:
            file = open ('detect.txt', 'w')
            file.write(str(ids[0][0]))
            file.close()
            time.sleep(1)
            #return (str(ids[0][0]))
        else:
            file = open ('detect.txt', 'w')
            file.write('None')
            file.close()
            time.sleep(1)
        # cv2.imshow("piCam", frame)
        # if cv2.waitKey(1) == ord('q'):
        #     break
    #cv2.destroyAllWindows()

detect()