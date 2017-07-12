#!/usr/bin/python3
# Streams stdin to the usha256_serial_slave sketch running on an Arduino,
# reads the computed hash, and prints the hash to stdout.

import sys
import serial
import time

if len(sys.argv) != 2:
    print("Usage:", sys.argv[0], "<serial device>")
    sys.exit(-1)

ser = serial.Serial(
    port=sys.argv[1],
    baudrate=115200,
    timeout=1
)

ser.setDTR(1)
time.sleep(1)
ser.setDTR(0)
time.sleep(2)
if ser.readline().decode('ascii') != "READY\r\n":
    print("Unable to initialize Arduino, did not receive READY string.")
    print("Verify code is uploaded, check connection, reset the")
    print("Arduino, and try again")
    sys.exit(-1)

while True:
    chunk = bytearray(sys.stdin.buffer.read(255))
    if len(chunk) > 0:
        # write data chunk size
        ser.write(bytearray([len(chunk)]))
        # write data chunk
        ser.write(chunk)
        # read number of bytes sucessfully hashed
        reply = ser.read(1)
        if reply[0] != len(chunk):
            print(reply[0], len(dataIn))
            print("error writing data to arduino")
            sys.exit(-1)
    if len(chunk) < 255:
        # end of input
        ser.write(bytearray([0x00]))
        break

hash = str(ser.read(64).decode('ascii').lower())
print(hash)
