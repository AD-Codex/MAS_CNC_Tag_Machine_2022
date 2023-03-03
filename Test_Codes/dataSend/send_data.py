
import serial
import serial.tools.list_ports
from struct import *
import sys
import time
import math

# x-77700, y=90000
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
        arduino.write(pack('32h', 1000,2000,3000,4000,5000,6000,7000,8000,9000,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200))
        data = arduino.readline()
        print("send data", data,"|")
        # time.sleep(0.8)
        
    except KeyboardInterrupt:
        break
    except:
        print(str(sys.exc_info()))
        break

    if ( int.from_bytes(data, 'big') == 3149066):
        print("re data")
        break

    