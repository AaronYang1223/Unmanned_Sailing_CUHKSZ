# File: main.py 
# Author: Baozhe Zhang, Lingpeng Chen
# Dedication to: Shiqi Yang
# Description: the main file of the autonomous driving sailboat

import serial
import sys
from lib.NatNetClient import NatNetClient
import math
import time
import multiprocessing as mp
from lib.boat import *

# Shifting parameters
_x_shift = 3.0
_y_shift = 2.0
# _theta_shift = - math.pi / 2 - 65 * math.pi / 180
_theta_shift = 0


def _mc_pos_tf(_x, _y):
    '''Changes the postion read from motion capture to a modelized pos
    '''
    return (_x + 3.0, _y - 2)
    # return (_y + _x_shift, -_x - _y_shift)


def data_stream(v):
    '''
    def receiveNewFrame(frameNumber, markerSetCount, unlabeledMarkersCount, rigidBodyCount, skeletonCount,
                    labeledMarkerCount, timecode, timecodeSub, timestamp, isRecording, trackedModelsChanged):
        return
    '''

    # This is a callback function that gets connected to the NatNet client. It is called once per rigid body per frame
    def receiveRigidBodyFrame(id, position, rotation):
        # position in meter
        # rotation in radius
        # print( "Received frame for rigid body", id )
        
        # only receive the info of the rigid body with the right id
        if (id == 141): 
            v[0] = position[0]
            v[1] = position[1]
            v[2] = position[2]
            
            v[3] = rotation[0]
            v[4] = rotation[1]
            v[5] = rotation[2]
            v[6] = rotation[3]

    # This will create a new NatNet client
    streamingClient = NatNetClient()

    # Configure the streaming client to call our rigid body handler on the emulator to send data out.
    # streamingClient.newFrameListener = receiveNewFrame
    streamingClient.rigidBodyListener = receiveRigidBodyFrame

    # Start up the streaming client now that the callbacks are set up.
    # This will run perpetually, and operate on a separate thread.
    streamingClient.run()
    
def main(v):
    time.sleep(2)
    boat = Boat()
    # this can be edited later for customized function

    def my_get_rudder_ins_func( x, y, theta ):
        ''' This is a customized function. 
        Before using and editing it, comment the below `boat.my_get_rudder_ins = None`
        and uncomment the below `boat.my_get_rudder_ins = my_get_rudder_ins_func` and 
        `mode = HEAD_WIND`. 
        Change the code below！
        '''
        if (y >= C[1]):
            mode = DOWN_WIND # 顺风模式
        if (mode == DOWN_WIND):
            return DOWN
        else:
            if (x >= L[0] and x < R[0]): # 在L和R之间
                if (theta >= 0 and theta < math.pi / 2.0): # 判断角度在0-90之间
                    return HEAD_R
                elif (theta >= math.pi / 2.0 and theta < math.pi): # 角度在90-180
                    return HEAD_L
                else:
                    return HEAD # 超出角度
            elif (x >= A[0] and x < L[0]): # 左边转右边
                return HEAD_R
            elif (x >= R[0] and x < B[0]): # 右边转左边
                return HEAD_L
            else:
                return HEAD

    boat.my_get_rudder_ins = None
    # boat.my_get_rudder_ins = my_get_rudder_ins_func
    # mode = HEAD_WIND

    try:
        ser = serial.Serial("COM7")
        while True:
            # print(v[0],' ',v[1],' ',v[2],' ',v[3],' ',v[4],' ',v[5],' ',v[6])    
            position = v[0:3]
            rotation = v[3:]
            
            [x, y, z, w] = rotation
            yaw = math.atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y))

            tf = _mc_pos_tf(position[0], position[1])
            ''' 
            some transformation info which is not needed

            # theta transformation
            if (yaw > - math.pi and yaw < 0):
                yaw += math.pi
            elif (yaw > 0 and yaw < math.pi):
                yaw -= math.pi

            if (yaw > 5/6 * math.pi and yaw < math.pi):
                yaw  = - (2 * math.pi - (yaw + 1 / 6 * math.pi))
            else:
                yaw += 1 / 6 * math.pi
            '''
            temp = (tf[0], tf[1], yaw)
            print(temp)

            boat.get_boat_position(temp)
            boat.send_ins(ser)


            time.sleep(1)

    except Exception as e:
        print(sys.argv[0] + ": ", e)


def multicore():
    v = mp.Array('d',[0,0,0,0,0,0,0]) # shared array [position and rotation]
    p1 = mp.Process(target=data_stream, args=(v,)) # process for reading
    p2 = mp.Process(target=main, args=(v,)) # process for calculating and sending
    p1.start()
    p2.start()
    p1.join()
    p2.join()

if __name__ == '__main__':
    multicore()
