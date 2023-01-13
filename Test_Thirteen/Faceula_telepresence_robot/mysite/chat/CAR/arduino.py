import serial
import time

def initConnection(portNo, baudRate):
	try:
		ser = serial.Serial(portNo, baudRate)
		print("Device Connected")
		return ser

	except:
		print("Not Connected")

def sendData(se, data, digits):
	myString = "$"
	for d in data:
		myString += str(d).zfill(digits)
		#print(myString)

	try:
		se.write(myString.encode())
		print(myString)

	except:
		print("Data transmission failed")


ser = initConnection("/dev/ttyACM0", 9600)

