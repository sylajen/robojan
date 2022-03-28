#code to test if the camera is working
from picamera import PiCamera
from time import sleep

camera = PiCamera()
camera.rotation = 180

camera.start_preview(alpha=200)
sleep(5)
camera.stop_preview()

