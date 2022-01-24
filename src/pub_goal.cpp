#include "ros/ros.h"
#include "move_base_msgs/MoveBaseGoal.h"
#include "std_msgs/String.h"
#include "ros_iat/pub_goal.h"
#include "geometry_msgs/Pose.h"


//goal {x, y}
goal_pos goal_list[3] = {
    {3.65, -3},
    {-7.6, -2.7},
    {2.420, 2.7}
};




SubscribeAndPublish::SubscribeAndPublish()  
{  
  //Topic you want to publish  
  pub_ = n_.advertise<geometry_msgs::Pose>("goal_pose", 1);  

  pub_voice = n_.advertise<std_msgs::String>("xfwords", 1);
      
  //Topic you want to subscribe  
  sub_ = n_.subscribe("iat_text", 1, &SubscribeAndPublish::callback, this);  //注意这里，和平时使用回调函数不一样了。
}  


void SubscribeAndPublish::callback(const std_msgs::String::ConstPtr& msg)
{
  std::string dataString = msg->data; 
  geometry_msgs::Pose goal;
  // const char* text;
  int goal_type = 0;
  if((dataString.find("1") != dataString.npos)||(dataString.find("一") != dataString.npos))
  {
    
    std_msgs::String V1;
    V1.data = "开始前往地点1";
    pub_voice.publish(V1);

    // char V1String[40] = "开始前往地点1";
    // text = V1String;
    // std::cout<<text<<std::endl;
    
    ROS_INFO("开始前往地点1");
    goal_type = 1;
  }  
  else if((dataString.find("2") != dataString.npos)||(dataString.find("二") != dataString.npos))
  {
    std_msgs::String V2;
    V2.data = "开始前往地点2";
    pub_voice.publish(V2);

    ROS_INFO("开始前往地点2");
    goal_type = 2;
  }
  else if((dataString.find("3") != dataString.npos)||(dataString.find("三") != dataString.npos))
  {
    std_msgs::String V3;
    V3.data = "开始前往地点3";
    pub_voice.publish(V3);

    ROS_INFO("开始前往地点3");
    goal_type = 3;
  }
  else
  {
    ROS_WARN("unrecognized command");
    // text = msg->data.c_str();
  }
  if(goal_type)
  {
    goal.position.x = goal_list[goal_type-1].goal_x;
    goal.position.y = goal_list[goal_type-1].goal_y;
    goal.orientation.x = 0;
    goal.orientation.y = 0;
    goal.orientation.z = 0.6;
    goal.orientation.w = 0.7;

 
    //.... do something with the input and generate the output...  
    pub_.publish(goal);  

    //重新进入自动巡逻模式-倒计时
    ros::param::set("/waitime", 300);

  }

}

 
int main(int argc, char **argv)
{  
    //Initiate ROS  
    ros::init(argc, argv, "goal_pub");  
      
    //Create an object of class SubscribeAndPublish that will take care of everything  
    SubscribeAndPublish iat_to_goal;  
      
    ros::spin();  
      
    return 0;  
}  






















// void iattextCallback(const std_msgs::String::ConstPtr& msg)
// {
//     char cmd[2000];
//     const char* text;
//     // move_base_msgs::MoveBaseGoal goal;
//     //     goal.target_pose.header.frame_id = "map";
//     //     goal.target_pose.header.stamp = ros::Time::now();
        
//     //     goal.target_pose.pose.position.x = goal_x;
//     //     goal.target_pose.pose.position.y = goal_y;
//     //     goal.target_pose.pose.orientation.w = goal_w;
//     //     goal_pub.publish(goal);


//     std::string dataString = msg->data;
//     if(dataString.find("地点1") != dataString.npos)
//     {
//         char forwordString[40] = "开始前往地点1";
//         text = forwordString;
//         std::cout<<text<<std::endl;
//         goal_type = 1;
//     }
//     else if(dataString.find("地点2") != dataString.npos)
//     {
//         char backwordString[40] = "开始前往地点2";
//         text = backwordString;
//         std::cout<<text<<std::endl;
//         goal_type = 2;
//     }
//     else if(dataString.find("地点3") != dataString.npos)
//     {
//         char leftString[40] = "开始前往地点3";
//         text = leftString;
//         std::cout<<text<<std::endl;
//         goal_type = 3;
//     }
//     else
//     {
//         ROS_WARN("unrecognized command");
//         text = msg->data.c_str();
//     }

// }






// int main(int argc, char **argv)
// {   

//     float goal_x = 0;
//     float goal_y = 0;
//     float goal

//     ros::init(argc, argv, "iat_goal_publisher");
//     ros::NodeHandle n;
//     ros::Publisher goal_pub = n.advertise<move_base_msgs::MoveBaseGoal>("iat_goal", 1000);
//     ros::Subscriber iat_text_sub =n.subscribe("iat_text", 1000, iattextCallback); //subscribe voice to text reault
//     ros::spin()
//     // ros::Rate loop_rate(10);
//     // while(ros::ok())
//     // {
//     //     /*code*/
//     //     move_base_msgs::MoveBaseGoal goal;
//     //     goal.target_pose.header.frame_id = "map";
//     //     goal.target_pose.header.stamp = ros::Time::now();
        
//     //     goal.target_pose.pose.position.x = goal_x;
//     //     goal.target_pose.pose.position.y = goal_y;
//     //     goal.target_pose.pose.orientation.w = goal_w;
//     //     goal_pub.publish(goal);
//     //     ros::spinOnce();
//     //     loop_rate::sleep();
//     // }

// }