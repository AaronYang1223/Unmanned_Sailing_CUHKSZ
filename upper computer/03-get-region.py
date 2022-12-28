#Copyright © 2018 Naturalpoint
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#http://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.


# OptiTrack NatNet direct depacketization sample for Python 3.x
#
# Uses the Python NatNetClient.py library to establish a connection (by creating a NatNetClient),
# and receive data via a NatNet connection and decode it using the NatNetClient library.

###################################################
# Editor: Baozhe Zhang
# Date: 2021/8/1
# Description: Use this file to demonstrate how to read information from Motion Capture and get the position of the sailboat. 
#              This file is edited for education purpose. 
###################################################

from lib.NatNetClient import NatNetClient
from lib.boat import *

boat = Boat()
# this can be edited later for customized function

def my_get_region_num_func( x, y ):
    ''' This is a customized function. 
    Before using and editing it, comment the below `boat.my_get_region_num = None`
    and uncomment the below `boat.my_get_region_num = my_get_region_num_func`. 
    The default library function is implemented as follows:
    '''
    if (y >= A[1] and y <= C[1]):
        return "REGION: 1"
    else:
        return "REGION: 2"

boat.my_get_region_num = None
# boat.my_get_region_num = my_get_region_num_func


# This is a callback function that gets connected to the NatNet client. It is called once per rigid body per frame
def receiveRigidBodyFrame( id, position, rotation ):
    # print( "Received frame for rigid body", id )
    if (id == 114):
        x = position[0]
        y = position[1]
        # theta here is not concerned
        boat.get_boat_position(x, y, 1.5)
        region_num = boat.get_region_num()
        print(region_num)

# This will create a new NatNet client
streamingClient = NatNetClient()

# Configure the streaming client to call our rigid body handler on the emulator to send data out.
streamingClient.rigidBodyListener = receiveRigidBodyFrame

# Start up the streaming client now that the callbacks are set up.
# This will run perpetually, and operate on a separate thread.
streamingClient.run()