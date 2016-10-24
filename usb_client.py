import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)
print("from Arduino: ",end="")
a=""
b=""
while True:
    b = ser.read()
    a += b.decode("utf8")
    print(b.decode("utf8"))
    if b == b'\n':
        print('Word: ' + a)