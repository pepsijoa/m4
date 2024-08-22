import RPi.GPIO as GPIO
import time

# GPIO 설정
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# 핀 설정
IN1 = 26
IN2 = 19
IN3 = 6
IN4 = 5
ENA = 13
ENB = 12

GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)
GPIO.setup(IN3, GPIO.OUT)
GPIO.setup(IN4, GPIO.OUT)
GPIO.setup(ENA, GPIO.OUT)
GPIO.setup(ENB, GPIO.OUT)

# PWM 설정
pwm_a = GPIO.PWM(ENA, 20000)
pwm_b = GPIO.PWM(ENB, 20000)
pwm_a.start(0)
pwm_b.start(0)

def set_motor_a(forward, speed):
    GPIO.output(IN1, forward)
    GPIO.output(IN2, not forward)
    pwm_a.ChangeDutyCycle(speed)

def set_motor_b(forward, speed):
    GPIO.output(IN3, forward)
    GPIO.output(IN4, not forward)
    pwm_b.ChangeDutyCycle(speed)

def move_forward(distance, speed=100):
    for i in range(100):	
        print(i)
        set_motor_a(True, i)
        set_motor_b(True, i)
        time.sleep(.2)
    #time.sleep(distance)
    stop()

def move_backward(distance, speed=100):
    set_motor_a(False, speed)
    set_motor_b(False, speed)
    time.sleep(distance)
    stop()

def turn_right(distance, speed=100):
    set_motor_a(True, speed)
    set_motor_b(False, speed)
    time.sleep(distance)
    stop()

def turn_left(distance, speed=100):
    set_motor_a(False, speed)
    set_motor_b(True, speed)
    time.sleep(distance)
    stop()

def stop():
    pwm_a.ChangeDutyCycle(0)
    pwm_b.ChangeDutyCycle(0)

def parse_command(command):
    direction, distance = command.split('\\')
    distance = float(distance)
    return direction, distance

try:
    while True:
        user_input = input("Enter command (e.g., R\\10, L\\10, F\\10, B\\10): ")
        direction, distance = parse_command(user_input)
        
        if direction == 'R':
            turn_right(distance)
            print("ok")  # 우회전 후 ok 출력
        elif direction == 'L':
            turn_left(distance)
            print("ok")  # 좌회전 후 ok 출력
        elif direction == 'F':
            move_forward(distance)
            print("ok")  # 전진 후 ok 출력
        elif direction == 'B':
            move_backward(distance)
            print("ok")  # 후진 후 ok 출력
        else:
            print("Invalid command")

except KeyboardInterrupt:
    pass

# 종료 처리
pwm_a.stop()
pwm_b.stop()
GPIO.cleanup()
