# ROS语音服务功能包:)
所涉及到的节点
## 1. iat_pub(语音-->文本):
    订阅：麦克风，支持连续输入，10秒输入时间，10秒休眠，依此循环
    发布：/iat_text话题，类型为std_msgs::String
## 2. goal_pub（文本-->目标点）:
    订阅：/iat_text
    发布：/goal_pose，类型为：geometry_msgs::Pose
## 3. tts_pub (语音合成：文本-->语音)：
    订阅：/xfwords,类型为：std_msgs::String
    发布：语音输出



# 后续配置注意：
    1.科大讯飞app_id
    2.arm平台的libmsc.so
    3.到达目标点后发布解说词至/xfwords话题

# 使用流程
    roslaunch ros_iat voice_control.launch
    //或分别rosrun，合在一个roslaunch似乎命令行没有相应的ROS::INFO/ROS::WARN输出
    rosrun ros_iat goal_pub
    rosrun ros_iat iat_pub
    rosrun ros_iat tts_pub


    1.目前目标点列表中有三个，使用麦克风时直接说出想去几号即可（1，2，3）。
    2. 配置目标点列表请至src/pub_goal.cpp