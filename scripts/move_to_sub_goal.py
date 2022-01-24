#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# 仿真测试
# 用于订阅src/pub_goal.cpp所发布的/iat_goal话题（目标点），类型为move_base_msgs::MoveBaseGoal
# 再跟据该目标点调用actionlib，完成导航流程
# 到达目标点后发布相应消息，经src/tts_subscribe_speak.cpp订阅后发出提示音“已到达”

import rospy
import actionlib
import roslib;
import rospy
from std_msgs.msg import String
 
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from geometry_msgs.msg import Pose


def nav_goal(pose):
    nav_goal = MoveBaseGoal()
    nav_goal.target_pose.header.frame_id = 'map'
    nav_goal.target_pose.header.stamp = rospy.Time.now()
    nav_goal.target_pose.pose = pose
    return nav_goal
 
def callback(pose):
	
    pub2 = rospy.Publisher('xfwords',String,queue_size = 1)
	if (msg.data.find('一') > -1):
        pose = waypoints[0]
        print('主人，准备出发一号站点请系好安全带！')
        pub2.publish('准备出发一号站点请系好安全带！')
        pub2.publish('准备出发一号站点请系好安全带！')
    elif msg.data.find('三') > -1:
        pose = waypoints[1]
        print ('主人，准备出发三号站点请系好安全带！')
        pub2.publish('准备出发三号站点请系好安全带！')
        pub2.publish('准备出发三号站点请系好安全带！')
    else:
        return

    client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    client.wait_for_server()        
    goal = nav_goal(pose)
    client.send_goal(goal)
    client.wait_for_result()



	if msg.data.find('一') > -1:
        print ('主人，一号站点已经到啦！')
        pub2.publish('主人，一号站点已经到啦！')
    elif msg.data.find('三') > -1:
        print ('主人，三号站点已经到啦！')
        pub2.publish('主人，三号站点已经到啦！')

 
if __name__ == '__main__':

    rospy.init_node('voice_nav_sim')

    pub = rospy.Publisher('voiceWakeup', String, queue_size = 1)

    rospy.sleep(1)
    pub.publish('wake up')

    sub = rospy.Subscriber('goal_pose', Pose, callback)
    rospy.spin()