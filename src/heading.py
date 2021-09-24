#!/usr/bin/env python
import roslib
import rospy
from nav_msgs.msg import Odometry
from math import degrees, radians
from tf.transformations import euler_from_quaternion, quaternion_from_euler

def wrap(value):
    if value < 0:
        return value + 360
    elif value >= 360:
        return value - 360
    else:
        return value

def odometryCb(msg):
    orientation_q = msg.pose.pose.orientation
    orientation_list = [orientation_q.y, orientation_q.x, -orientation_q.z, orientation_q.w]
    orientation_list_1 = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
    (roll, pitch, yaw) = euler_from_quaternion (orientation_list)
    (roll_1, pitch_1, yaw_1) = euler_from_quaternion (orientation_list_1)
    print("world frame :",wrap(degrees(yaw) + 90))
    print("ROS frame :",wrap(degrees(yaw_1)))

if __name__ == "__main__":
    rospy.init_node('odometry', anonymous=True) #make node 
    rospy.Subscriber('odometry/filtered_map',Odometry,odometryCb)
    rospy.spin()
