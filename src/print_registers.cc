#include <memory>
#include <stdexcept>

#include <ros/ros.h>

#include <cmu_16662_robot_utils/robauton_utils.h>


namespace rau = robauton_utils;

namespace print_registers
{
class RegisterReaderNode
{
public:
  RegisterReaderNode() : node_handle_("")
  {
    // Get parameters from ROS parameter server
    std::string device_name;
    if (!node_handle_.getParam("device_name", device_name))
    {
      const std::string error_msg("Could not get ROS parameter \"device_name\".");
      ROS_FATAL_STREAM(error_msg);
      throw std::runtime_error(error_msg.c_str());
    }

    int baud_rate;
    if (!node_handle_.getParam("baud_rate", baud_rate))
    {
      const std::string error_msg("Could not get ROS parameter \"baud_rate\".");
      ROS_FATAL_STREAM(error_msg);
      throw std::runtime_error(error_msg.c_str());
    }

    int scan_range;
    if (!node_handle_.getParam("scan_range", scan_range))
    {
      const std::string error_msg("Could not get ROS parameter \"scan_range\".");
      ROS_FATAL_STREAM(error_msg);
      throw std::runtime_error(error_msg.c_str());
    }

    // Create servo register reader
    reg_reader_ = std::make_unique<rau::RegisterReader>(device_name, baud_rate, scan_range);
  }
  void print_servo_registers() const
  {
    reg_reader_->print_servo_registers();
  }

private:
  ros::NodeHandle node_handle_;
  std::unique_ptr<rau::RegisterReader> reg_reader_;
};

} // print_registers


int main(int argc, char** argv)
{
  // Init ROS node
  ros::init(argc, argv, "print_registers");
  print_registers::RegisterReaderNode reg_reader_node;
  reg_reader_node.print_servo_registers();
  ros::spin();
  
  return 0;
}
