#include "ros/init.h"
#include "ros/node_handle.h"
#include <ros/ros.h>
#include <unit6_exercises/magic_subscriber_function.h>
#include <sensor_msgs/PointCloud2.h>

int main(int argc, char**argv){
    ros::init(argc,argv,"magic_pcl_susbcriber_main_node");
    ros::NodeHandle _n("magic_pcl_susbcriber_main_ns");
    MagicSubscriber masb;
    string tp = "/camera/depth_registered/points";
    masb.init<sensor_msgs::PointCloud2>(_n, tp);
    ros::spin();
}