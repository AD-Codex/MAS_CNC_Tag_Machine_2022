
import serial
import serial.tools.list_ports
from struct import *
import sys
import time
import math
import numpy as np


geoCoords =[(314, -81),
            (314, -91),
            (314, -101),
            (314, -111),
            (324, -111),
            (334, -111),
            (344, -111),
            (354, -111),
            (354, -101),
            (354, -91),
            (354, -81),
            (344, -81),
            (334, -81),
            (324, -81),
            (314, -81)
            # (115.46,	235.07),
            # (379.47,	148.21),
            # (110.07,	147.96),
            # (110.07,	60.12)            
            ]

PULSES_MM_X = 11.14 #total 628mm 11
PULSES_MM_Y = 55.55 #total 162mm 145

coords = np.asarray(geoCoords)
coords[:,0] = coords[:,0]*PULSES_MM_X
coords[:,1] = coords[:,1]*PULSES_MM_Y

coords = np.round(coords,0).astype('int')

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





pointSize = len(coords)*2
arrSize = 30
numChunks = np.ceil(pointSize/arrSize).astype(int)
chunkList = []

for n in range(0,numChunks):
    ch = np.ones((arrSize,1),dtype='int')
    ch = ch * (-1)
    chunkList.append(ch)

start = 0
#split the entire cordinates in to chunks of 30x1
for n in range(0,numChunks):
    try:
        chunk = coords[start : n+int(arrSize/2),:]
        chunk =  np.reshape(chunk,(30,1))
        chunkList[n][start:] = chunk
        start = start + int(arrSize/2)
    
    except:
        chunk = coords[start:,:]
        le = len(chunk)
        chunk =  np.reshape(chunk,(le*2,1))
        chunkList[n][0:le*2] = chunk

        

start =  time.time()

for chunk in chunkList:

    count = 0
    read = []
    while (True):
        # try:
        # arduino.write(pack('24h', 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 1, 2, 3, 4))
        # arduino.write(pack('30h',coords[0,0],coords[0,1],coords[1,0],coords[1,1],
        #                    coords[2,0],coords[2,1],coords[3,0],coords[3,1],
        #                    coords[4,0],coords[4,1],coords[5,0],coords[5,1],
        #                    coords[6,0],coords[6,1],coords[7,0],coords[7,1],
        #                    coords[8,0],coords[8,1],coords[9,0],coords[9,1],
        #                    coords[10,0],coords[10,1],coords[11,0],coords[11,1],
        #                    coords[10,0],coords[10,1],coords[11,0],coords[11,1],
        #                    coords[0,0],coords[0,1]))
        
        arduino.write(pack('30h',chunk[0,0],chunk[1,0],chunk[2,0],chunk[3,0],chunk[4,0],
                           chunk[5,0],chunk[6,0],chunk[7,0],chunk[8,0],chunk[9,0],
                           chunk[10,0],chunk[11,0],chunk[12,0],chunk[13,0],chunk[14,0],
                           chunk[15,0],chunk[16,0],chunk[17,0],chunk[18,0],chunk[19,0],
                           chunk[20,0],chunk[21,0],chunk[22,0],chunk[23,0],chunk[24,0],
                           chunk[25,0],chunk[26,0],chunk[27,0],chunk[28,0],chunk[29,0]))
        
        
        data = str(arduino.readline())
        string = data.split()
        string = string[0][2:len(string[0])-5]
        print("recv data", count, string)
    
        if len(string) != 0:
            # time.sleep(0.05)
            count = count+1
            read.append(int(string))
        
        
        if count == 30:           
            read = np.asarray(read)
            if len(read) == len(chunk):   
                read = np.reshape(read,(30,1))
                
                if np.array_equal(read, chunk):
                    print('Transfer success')
                    break
                else: 
                    print('Data mistmatch')
                    break
            else:
                print('Data length mistmatch')
                break   
            
            
        # except:
        #     print('breaking')
        #     break
        # break
        
    end = time.time()    
    x = end -start
    print(x)
    # arduino.close()
    # arduino.open()
    break




