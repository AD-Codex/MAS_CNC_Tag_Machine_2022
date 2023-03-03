
import serial
import serial.tools.list_ports
from struct import *
import sys
import time
import math

# x-77700, y=90000

geoCoords = [(3500, -4500),
             (3500, -3500),
             (3500, -5500),
             (4500, -3500),
             (0, -9000),
             (9999, 9999)]
             # (0, 0),
             # (3500, -4500),
             # (0, 0),
             # (3500, -4500),
             # (1897, -1234),
             # (5674, -1234),
             # (2345, -3456),
             # (4567, -5678),
             # (6789, -7890),
             # (1890, -9000),
             # (123, -1234),
             # (9999, 9999)]

print(geoCoords[0])

try:
    print('Please Connect a Communication Port')
    while True:
        ports = list(serial.tools.list_ports.comports())
        if ports:
            break
    
    for p in ports:
        if ("Arduino" in p.description or "USB Serial Device" in p.description):
            com = p.device
            print(com)
            break
    print('Communication Port : Connected\n')
    arduino = serial.Serial( baudrate='115200', timeout=1.0, port=com)  # change timeout=1.0 for arduino Mega | timeout=0.1 for Arduino uno


except:
    print('ERROR: Could not connect to arduino')




i = 0

while (True):
    
    try:
    	arduino.write(pack('2h', geoCoords[i][0], geoCoords[i][1] ))
    	data = arduino.readline()
    	print("send data", data,"|")
    	time.sleep(0.1)
    	
    except KeyboardInterrupt:
        break
    except:
        print(str(sys.exc_info()))
        break

    if ( int.from_bytes(data, 'big') == 3149066):
    	# print("re data")
    	if ( i < len(geoCoords)-1):
    		i=i+1

    