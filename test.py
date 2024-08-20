from picamera2 import Picamera2
import cv2

picam2 = Picamera2()


camera_config = picam2.create_preview_configuration()
picam2.configure(camera_config)


picam2.start()

while True:

    frame = picam2.capture_array()
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    cv2.imshow("Camera", frame)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


picam2.stop()
cv2.destroyAllWindows()
