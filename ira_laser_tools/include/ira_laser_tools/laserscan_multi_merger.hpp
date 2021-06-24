#ifndef IRA_LASER_TOOLS_LADERSAN_MULTI_MERGER_HPP_
#define IRA_LASER_TOOLS_LADERSAN_MULTI_MERGER_HPP_

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <math.h>

#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer_interface.h"
#include "pcl_conversions/pcl_conversions.h"
#include "pcl/point_cloud.h"
#include "rclcpp/rclcpp.hpp"

#include "laser_geometry/laser_geometry.hpp"
#include "pcl_ros/transforms.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"

namespace laserscan_multi_merger
{
class LaserscanMerger : public rclcpp::Node
{
public:
  LaserscanMerger();
  void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr scan, std::string topic);
  void pointcloud_to_laserscan(sensor_msgs::msg::PointCloud2::ConstSharedPtr cloud_msg);
  void laserscan_topic_parser();
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tfListener_;

private:
  laser_geometry::LaserProjection projector_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_publisher_;
  rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr laser_scan_publisher_;
  std::vector<rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr> scan_subscribers;
  std::vector<bool> clouds_modified;
  std::vector<pcl::PCLPointCloud2> clouds;
  std::vector<std::string> input_topics;
  std::vector<std::string> subscribed_topics;
  rclcpp::TimerBase::SharedPtr topic_parser_timer;

  double angle_min;
  double angle_max;
  double angle_increment;
  double time_increment;
  double scan_time;
  double range_min;
  double range_max;
  double inf_epsilon;
  bool use_inf;

  double min_height;
  double max_height;

  std::string destination_frame;
  std::string cloud_destination_topic;
  std::string scan_destination_topic;
  std::string laserscan_topics;
};

}  // namespace laserscan_multi_merger

#endif  // IRA_LASER_TOOLS_LADERSAN_MULTI_MERGER_HPP_