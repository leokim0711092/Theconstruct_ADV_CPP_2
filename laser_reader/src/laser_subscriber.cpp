#include "ros/node_handle.h"
#include "ros/subscriber.h"
#include <memory>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class LaserSubscriberNode{
    public:
        LaserSubscriberNode(): laser_scan(nullptr) //Initialize the laser_scan as nullptr
        {   
            ros::NodeHandle nh;
            laser_sub = nh.subscribe("kobuki/laser/scan",10, &LaserSubscriberNode::laser_subscribe_callback, this);
        
        }
        void printClosestObstacleDistance() const{
            float min_range = laser_scan -> ranges[0];
            int rc;
            for(int i=0;i<laser_scan->ranges.size();i++){
                if(laser_scan->ranges[i] < min_range){
                    min_range = laser_scan->ranges[i];
                    rc = i;
                }
            }
            float angle = laser_scan->angle_min + rc * laser_scan->angle_increment;
            // Print the distance to the closest obstacle and the corresponding angle in
            // radian
            std::cout << "Closest obstacle distance: " << min_range
                    << ", Angle (rad): " << angle << std::endl;
        }
    private:
        ros::Subscriber laser_sub;
        std::shared_ptr<sensor_msgs::LaserScan> laser_scan; // define the constant pointer laser_scan
        void laser_subscribe_callback(const sensor_msgs::LaserScanConstPtr &msg){
            laser_scan = std::make_shared<sensor_msgs::LaserScan>(*msg);
            if(!laser_scan->ranges.empty() && laser_scan != nullptr){
                printClosestObstacleDistance();
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