
import serial
import serial.tools.list_ports
from struct import *
import sys
import time
import math
import numpy as np


geoCoords =[(314,     0),
            (314,    -162),
            (628,	-162),
            (628,	-81),
            (314,	0),
            (110.07,	-147.96),
            (110.07,	-60.12),
            (379.71,	-60.12),
            (100,       -200),
            (300,       -400),
            (25,        -60),
            (544,       -545),
            (25,        -60),
            (544,       -545),
            (77,     -26.5),
            (88,	-235.07),
            (379.47,	148.21),
            (110.07,	147.96),
            (385.35,26.75),
            (385.35,	235.07),
            (115.46,	235.07),
            (379.47,	148.21)
            (110.07,	147.96),
            (110.07,	60.12),
            (379.71,	60.12),
            (100,       200),
            (300,       400),
            (25,        60),
            (544,       545),
            (25,        60),
            (544,       545),
            (77,     26.5),
            (88,	235.07),
            (379.47,	148.21),
            (110.07,	147.96),
            (115.46,	235.07),
            (379.47,	148.21),
            (110.07,	147.96),
            (385.35,26.75),
            (385.35,	235.07)
            # (115.46,	235.07),
            # (379.47,	148.21),
            # (110.07,	147.96),
            # (110.07,	60.12),
            # (379.71,	60.12),
            # (100,       200),
            # (300,       400),
            # (25,        60),
            # (544,       545),
            # (25,        60),            
            # (110.07,	60.12)            
            ]

# geoCoords= [(337.51, -37.88),
#        (397.23, -39.89),
#        (399.22, -76.1 ),
#        (342.24, -80.3 )]

PULSES_MM_X = 11.14
PULSES_MM_Y = 55.55


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
        chunk = coords[start : start+int(arrSize/2),:]
        chunk =  np.reshape(chunk,(30,1))
        chunkList[n][0:] = chunk
        start = start + int(arrSize/2)
    
    except:
        chunk = coords[start:,:]
        le = len(chunk)
        chunk =  np.reshape(chunk,(le*2,1))
        chunkList[n][0:le*2] = chunk

## Create an array of -1 to indicate a data loss
flagArr = np.ones((arrSize,1)).astype('int')
flagArr = -1*flagArr
  

      
## Start sending
start =  time.time()
c = 0
flag = 1
while c < len(chunkList):    
    if flag == -1:
        chunk = flagArr
    else:   
        chunk =  chunkList[c]
    chunk =  chunkList[c]
    count = 0
    read = []
    while (True):        
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
        print("checking...........")
        time.sleep(0.1)

        if ( string == str(np.sum(chunk))):
            print("Transfer success")
            c=c+1
            break
        else:
            print("Transfer not success", np.sum(chunk))
            flag = -1
            break

                    
    end = time.time()    
    seconds = end -start
    print(seconds,"\n")

while(True):
    data = str(arduino.readline())
    string = data.split()
    string = string[0][2:len(string[0])-5]
    print("Arduino data ", string)

