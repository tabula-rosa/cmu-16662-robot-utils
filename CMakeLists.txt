cmake_minimum_required(VERSION 2.8.3)

project(cmu_16662_robot_utils)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  dynamixel_workbench_toolbox
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    roscpp
    dynamixel_workbench_toolbox
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/robauton_utils.cc
)

add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})

add_executable(${PROJECT_NAME}_print_registers
  src/print_registers.cc
)

set_target_properties(${PROJECT_NAME}_print_registers
  PROPERTIES OUTPUT_NAME print_registers PREFIX "")

target_link_libraries(${PROJECT_NAME}_print_registers
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
  ~/ws/test/devel/lib/libdynamixel_workbench_toolbox.so # fix later
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_print_registers
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
