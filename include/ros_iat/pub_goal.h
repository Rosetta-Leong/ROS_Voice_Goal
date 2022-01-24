#ifndef _PUB_GOAL_H_
#define _PUB_GOAL_H_

#include "ros/ros.h"
#include "std_msgs/String.h"

typedef struct 
{
    float goal_x;
    float goal_y;
}goal_pos;

class SubscribeAndPublish  
{  
    public:  
      SubscribeAndPublish();
      void callback(const std_msgs::String::ConstPtr& msg);
      
    private:  
      ros::NodeHandle n_;   
      ros::Publisher pub_;  //publish /goal_pose
      ros::Subscriber sub_; //subscribe  /iat_text
      ros::Publisher pub_voice; //publish some voice
};

#endif