#ifndef CMU_16662_ROBOT_UTILS_INCLUDE_CMU_16662_ROBOT_UTILS_ROBAUTON_UTILS_H_
#define CMU_16662_ROBOT_UTILS_INCLUDE_CMU_16662_ROBOT_UTILS_ROBAUTON_UTILS_H_

#include <string>

#include <dynamixel_workbench_toolbox/dynamixel_workbench.h>


namespace robauton_utils
{
class RegisterReader
{
public:
  RegisterReader(const std::string& device_name = "/dev/ttyUSB0",
                 const uint32_t& baud_rate = 1000000,
                 const uint8_t& scan_range = 10);
  void print_servo_registers() const;

private:
  DynamixelWorkbench* dxl_wb_;
  uint8_t dxl_id_[16];
  uint8_t dxl_cnt_;
};

} // namespace robauton_utils

#endif // CMU_16662_ROBOT_UTILS_INCLUDE_CMU_16662_ROBOT_UTILS_ROBAUTON_UTILS_H_
