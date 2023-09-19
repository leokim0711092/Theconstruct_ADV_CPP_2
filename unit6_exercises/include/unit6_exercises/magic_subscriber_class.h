#ifndef MAGIC_SUBSCRIBER_H
#define MAGIC_SUBSCRIBER_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

using namespace std;

template<typename RosNT>class MagicSubscriber {
public:
  MagicSubscriber(ros::NodeHandle &ros_node, const string subscriber_topic){
    this->m_ros_node_object = &ros_node;
    this->m_subscriber_topic = subscriber_topic;
    if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,ros::console::levels::Info)) {
      ros::console::notifyLoggerLevelsChanged();
    }
    image_sub_ = this->m_ros_node_object->subscribe(this->m_subscriber_topic,1,&MagicSubscriber::CallbackToTopic<RosNT>,this);
  }
  ~MagicSubscriber(){ cout << "MagicSubscriber Destructor is called" << endl;}

  template<typename CallBackRosNT>
  void CallbackToTopic(const typename RosNT::ConstPtr &msg){
  // the uint8 is an alias of unsigned char, therefore needs casting to int
    ROS_INFO_STREAM(
        "Call Back Topic Image Data[0]=" << static_cast<int>(msg->data[0]));
  }

private:
  ros::NodeHandle *m_ros_node_object;
  string m_subscriber_topic;
  ros::Subscriber image_sub_;
};

#endif