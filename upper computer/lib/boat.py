# File: boat.py 
# Author: Baozhe Zhang
# Description: boat module 


import math

# Coordinates of the pool
A = (0, 0)
B = (6, 0)
C = (6, 4)
D = (6, 6)
E = (0, 6)
F = (0, 5.5)
# G = (0, 4)
# H = (4, 4)
L = (2, 0)
R = (4, 0)

# Sailing mode
HEAD_WIND = 0
DOWN_WIND = 1
# TURNING = 2

# Directives for low-level controller
HEAD_L = b"150"
HEAD_R = b"030"
HEAD   = b"090"
# TURN = b"A020"
DOWN = b"270"
# TIGHT = b"C010"
# LOOSE = b"C090"


class Boat():

    def __init__(self, x=2, y=0, theta=0):
        self.cx = x
        self.cy = y
        self.ctheta = theta  # in degree
        self.mode = HEAD_WIND
        self.on = True
        self.my_get_rudder_ins = None # customized func
        self.my_get_region_num = None # customized func

    def get_boat_position(self, temp):
        '''get and update (x, y, theta)
        '''
        self.cx = temp[0]
        self.cy = temp[1]
        self.ctheta = temp[2]
        # print(temp)
        return (self.cx, self.cy, self.ctheta)

    def get_rudder_ins(self):
        '''get the instruction for rudder
        '''
        if (self.my_get_rudder_ins == None): # default strategy
            if (self.cy >= C[1]):
                self.mode = DOWN_WIND
            if (self.mode == DOWN_WIND):
                return DOWN
            else:
                if (self.cx >= L[0] and self.cx < R[0]):
                    if (self.ctheta >= 0 and self.ctheta < math.pi / 2.0):
                        return HEAD_R
                    elif (self.ctheta >= math.pi / 2.0 and self.ctheta < math.pi):
                        return HEAD_L
                    else:
                        return HEAD
                elif (self.cx >= A[0] and self.cx < L[0]):
                    return HEAD_R
                elif (self.cx >= R[0] and self.cx < B[0]):
                    return HEAD_L
                else:
                    return HEAD
        else: # custom strategy
            x = self.cx 
            y = self.cy
            theta = self.ctheta
            return self.my_get_rudder_ins( x, y, theta )
    
    def get_region_num(self):
        if (self.my_get_region_num == None):
            if (self.cy >= A[1] and self.cy <= C[1]):
                return "REGION: 1"
            else:
                return "REGION: 2"
        else:
            x = self.cx
            y = self.cy
            return self.my_get_region_num( x, y )

    def send_ins(self, ser):
        '''send instruction to boat
        and send the current theta
        '''
        def convertAngle(angle):
            '''convert the angle in radius to 
            a 3-byte string for sending it later
            '''
            angle = angle / math.pi * 180
            angle = int(angle)
            angle = str(angle)
            result = ""
            if (angle[0] == '-'):
                # result += "B"

                result += str(int(angle)+360)
            else:
                # result += "A" 
                if (len(angle) > 2):
                    result += angle
                elif (len(angle) == 1):
                    result += "00"
                    result += angle
                else:
                    result += '0'
                    result += angle

            if (len(result) != 3):
                result = "0" + result
            # print(result)
            return bytes(result, 'ascii')

        try:
            temp = self.get_rudder_ins()
            angle_bytes = convertAngle(self.ctheta)
            send_data = bytes(angle_bytes.decode() + temp.decode(), 'ascii')
            print("[Boat.send_ins]:", send_data.decode())
            ser.write(send_data)

        except Exception as e:
            print(e)

