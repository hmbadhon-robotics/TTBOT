import time
import arduino


def direction(d):
	if d == "forward": forward()
	elif d == "reverse": reverse()
	elif d == "left": left()
	elif d == "right": right()
	else: stop()

def forward():
    print("1")
    sendData(ser, [1], 1)
	#time.sleep(1)	

def reverse():
    print("2")
    sendData(ser, [2], 1)
	#time.sleep(1)
	
def left():
    print("3")
    sendData(ser, [3], 1)
	#time.sleep(1)

def right():
    print("4")
    sendData(ser, [4], 1)
	#time.sleep(1)

def stop():
    print("5")
    sendData(ser, [5], 1)
	#time.sleep(1)


