cmake_minimum_required(VERSION 2.8.3)
project(nostop_rviz_visual)

ENABLE_LANGUAGE(CXX)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(catkin REQUIRED COMPONENTS 
  roslib
  roscpp 
  rospy
  std_msgs 
  base_math
  tf
  nav_msgs
)



## Generate added messages and services with any dependencies listed here
#  generate_messages(
#    DEPENDENCIES
#    std_msgs  # Or other packages containing msgs
#    )

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include/${PROJECT_NAME}/
  LIBRARIES ${PROJECT_NAME}
  DEPENDS roscpp rospy base_math
)



###########
## Build ##
###########
include_directories(include/${PROJECT_NAME}/ ${catkin_INCLUDE_DIRS})

link_directories(${catkin_LIBRARY_DIRS})
include_directories(src/)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)
include_directories(${CMAKE_INSTALL_PREFIX}/include) # this line is to find lemon include files.
include_directories(${OpenCV_INCLUDE_DIRS})


set(rviz_visual_SOURCES
        src/rviz_visual_node.cpp
        src/Rviz_visual.cpp
)


add_executable(rviz_visual_node ${rviz_visual_SOURCES})
add_dependencies(rviz_visual_node nostop_rviz_visual_gencpp)
target_link_libraries(rviz_visual_node ${catkin_LIBRARIES} base_math)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
 install(TARGETS rviz_visual_node
 EXPORT nostop_rviz_visual
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )
 
 