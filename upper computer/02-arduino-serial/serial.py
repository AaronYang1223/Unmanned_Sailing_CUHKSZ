import serial

def main():
    ser = serial.Serial(port="COM7", baudrate=9600)
    while True:
        command = input("Enter a command (e.g., 0001): ")
        ser.write(bytes(command, "ascii"))
        print(ser.readline())
        print(ser.readline())
        print(ser.readline())
    