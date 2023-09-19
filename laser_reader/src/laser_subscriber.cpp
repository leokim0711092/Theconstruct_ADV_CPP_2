#include "ros/node_handle.h"
#include "ros/subscriber.h"
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class LaserSubscriberNode{
    public:
        LaserSubscriberNode(): laser_scan(nullptr) //Initialize the laser_scan as nullptr
        {   
            ros::NodeHandle nh;
            laser_sub = nh.subscribe("kobuki/laser/scan",10, &LaserSubscriberNode::laser_subscribe_callback, this);
        
        }
    private:
        ros::Subscriber laser_sub;
        const sensor_msgs::LaserScan *laser_scan; // define the constant pointer laser_scan
        void laser_subscribe_callback(const sensor_msgs::LaserScanConstPtr &msg){
            laser_scan = msg.get();
            if(!laser_scan->ranges.empty()){
                float r = laser_scan->ranges[360];
                ROS_INFO("Range: %f",r);
            }
        }
};

int main(int argc, char** argv)
{
  // Initialize the ROS node
  ros::init(argc, argv, "laser_subscriber_node");

  // Create an instance of the LaserSubscriberNode class
  LaserSubscriberNode node;

  // Spin the node
  ros::spin();

  return 0;
}