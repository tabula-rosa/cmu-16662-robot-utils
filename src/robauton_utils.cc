#include <iostream>
#include <stdexcept>
#include <string>

#include <dynamixel_workbench_toolbox/dynamixel_tool.h>
#include <dynamixel_workbench_toolbox/dynamixel_workbench.h>

#include <cmu_16662_robot_utils/robauton_utils.h>


namespace robauton_utils
{
RegisterReader::RegisterReader(const std::string& device_name,
                               const uint32_t& baud_rate,
                               const uint8_t& scan_range)
{
  // Setup workbench and scan for controller
  dxl_wb_ = new DynamixelWorkbench;
  dxl_wb_->begin(device_name.c_str(), baud_rate);

  if (dxl_wb_->scan(dxl_id_, &dxl_cnt_, scan_range) != true)
  {
    throw std::runtime_error(std::string("Could not find robot servos.").c_str());
  }
}

void RegisterReader::print_servo_registers() const
{
  for (int index = 0; index < dxl_cnt_; index++)
  {
    uint8_t servo_id = dxl_id_[index];
    std::string model_name(dxl_wb_->getModelName(servo_id));
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Servo enumeration: " << index << std::endl;
    std::cout << "Servo ID: " << static_cast<int>(servo_id) << std::endl;
    std::cout << "Model: " << model_name << std::endl;

    // getConrolTableItem
    DynamixelTool dxl_tool;
    dxl_tool.addTool(model_name.c_str(), servo_id);
    ControlTableItem* item_ptr = dxl_tool.getControlItemPtr();

    for (int r = 0; r < dxl_tool.getTheNumberOfItem(); r++)
    {
      std::string reg_name = item_ptr[r].item_name;
      std::cout << r << " - " << reg_name << ": "
                << dxl_wb_->itemRead(servo_id, reg_name.c_str()) << std::endl;
    }
  }
}

} // namespace robauton_utils
