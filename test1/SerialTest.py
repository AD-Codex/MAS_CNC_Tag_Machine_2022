import numpy as np
import serial
import serial.tools.list_ports
from struct import *
import time
import math

geoCoords = [(34, -52), ##748 1144
             (12, 12),  ##264 264
             (143, 15), ## 3146 330
             (115, -235), ##2530  5170
             (-379, 148), ##8338  3256
             (-110, 147), ##2420  3234
             (-110, -60), ##2420  1320
             (-379, -60), ##8338 1320
             (-232, -32)] ##5104 704



def GenerateGode(geoCoords):
    PULSES_MM_X = 1
    PULSES_MM_Y = 1
    
    coords = np.asarray(geoCoords)
    # coords = np.reshape(coords,(coords.shape[0]*coords.shape[1],2))
    coords[:,0] = coords[:,0]*PULSES_MM_X
    coords[:,1] = coords[:,1]*PULSES_MM_Y  
    
    try:
        print('Please Connect a Communication Port')
        while True:
            ports = list(serial.tools.list_ports.comports())
            if ports:
                break

        for p in ports:
            print (p)
            if ("Arduino" in p.description or "USB Serial Device" in p.description):
                com = p.device
                break
        print('Communication Port : Connected\n')
        ser = serial.Serial(baudrate='115200', timeout=1.0,
                            port=com)  # change timeout=1.0 for arduino Mega | timeout=0.1 for Arduino uno

    except:
        print('ERROR: Could not connect to arduino')

    time.sleep(1)

    # checkIntvl = int(geoCoords[0].shape[0])
    checkIntvl = 4
    start, flag = sendSerial(ser, coords, checkIntvl)

    while (flag != 4):
        flag = finalCheck(ser, len(coords), flag, coords, checkIntvl)

    end = time.time()
    ser.close()
    print('Transferring Completed!')
    elapsed = print(end - start)

    return


def sendSerial(ser, coords, checkIntvl):
    count = 0
    i = 0
    flag = 0

    print('Transferring Gcodes..')
    start = time.time()
    # for i in range(len(coords)):
    while (True):
        print("loop = ", i, "-", coords[i, 0], coords[i, 1] )
        length = 0
        ser.write(pack('3h', coords[i, 0], coords[i, 1], 0))  # f for float
        time.sleep(1)

        # print(ser.inWaiting())
        while ser.in_waiting:
            length, s = readSerial(ser, length)

        count = count + 1
        print("")
        i = i + 1
        # ser.close()
        # ser.open()
        time.sleep(2)

        ## Handshake every checkIntvl times
        if count == checkIntvl - 1:
            print('Checking..')
            # ser.reset_input_buffer()
            count = 0
            length = 0
            params = []
            ser.write(pack('3f', coords[i, 0], coords[i, 1], 1.0))  # signal to Handshake
            time.sleep(0.8)
            # ser.reset_output_buffer()

            while (ser.in_waiting):
                length, string = readSerial(ser, length)
                if string:
                    params.append(float(string[0][2:len(string[0]) - 5]))

            if length >= 3:
                params = np.asarray(params)
                meanX = math.trunc(np.mean(coords[0:i + 1, 0]))  # rounded to nearest integer
                meanY = math.trunc(np.mean(coords[0:i + 1, 1]))  # rounded to nearest integer
                cnt = i+1
                print('Arduino ', params[0], 'Python ', meanX)
                print('Arduino ', params[1], 'Python ', meanY)
                print('Arduino ', params[2], 'Python ', cnt)


                if (params[0] == meanX and params[1] == meanY and params[2] == cnt):
                    i = i + 1
                    pass
                else:
                    print("")
                    print('Re-sending last ' + str(checkIntvl) + ' arrays')
                    length = 0
                    flag = 2
                    reSendData(ser, length, checkIntvl, flag)
                    i = i - checkIntvl + 1
                    # break ## break to re-send

        ser.reset_input_buffer()
        ser.reset_output_buffer()

        if i == (len(coords)):

            flag = 3
            break

    return start, flag


def readSerial(serial, length):
    dat = serial.readline()
    print(dat)

    if dat != b'' and dat != b'\r\n':
        length = length + 1
        string = str(dat).split()
        print(string[0][2:len(string[0]) - 5])

    else:
        string = None

    return length, string


def reSendData(ser, length, replaceSize, flag):
    # ser.close()
    # ser.open()
    time.sleep(2)

    while (True):
        ser.write(pack('3f', 0, replaceSize, flag))  # signalling the re-send
        time.sleep(0.5)
        ser.reset_output_buffer()
        break

        # #####
        # length, string = readSerial(ser, length)
        # if length >= 3:
        #     ser.close()
        #     # sleep(0.1)
        #     ser.open()
        #     print("")
        #     break
        # # else:
        # #     break


def finalCheck(ser, arrSize, flag, coords, checkIntvl):
    # ser.close()
    # ser.open()
    time.sleep(2)

    print('final check')
    params = []
    length = 0
    x = len(coords) - 1
    while (True):
        ser.write(pack('3f',2,4, flag))
        time.sleep(0.5)
        ser.reset_output_buffer()

        #####
        length, string = readSerial(ser, length)
        if string:
            params.append(float(string[0][2:len(string[0]) - 5]))

        if length >= 3:
            params = np.asarray(params)
            meanX = math.trunc(np.mean(coords[:, 0]))  # rounded to nearest integer
            meanY = math.trunc(np.mean(coords[:, 1]))  # rounded to nearest integer
            cnt = len(coords)
            print('Arduino LAST ', params[0], 'Python LAST ', meanX)
            print('Arduino LAST ', params[1], 'Python LAST ', meanY)
            print('Arduino LAST ', params[2], 'Python LAST ', cnt)
            if (params[0] == meanX and params[1] == meanY and params[2] == cnt):
                flag = 4
                ser.write(pack('3f', 0, 0, flag))
                break
            else:
                print("")
                print('Re-sending all data')
                length = 0
                reSendData(ser, length, arrSize, flag)  # signalling the re-send
                sendSerial(ser, coords, checkIntvl)
                break
    return flag


if __name__ == "__main__":

    GenerateGode(geoCoords)
