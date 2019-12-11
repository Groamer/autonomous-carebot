cmake_minimum_required(VERSION 2.8.3)
project(cim_turtlebot3_localization)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	genmsg
)

catkin_package()

include_directories(
	include ${catkin_INCLUDE_DIRS}
)

add_executable(
	cim_turtlebot3_localization
	src/LocalizationApp.cpp
)
target_link_libraries(
	cim_turtlebot3_localization
	${catkin_LIBRARIES}
)
add_dependencies(
	cim_turtlebot3_localization
	cim_turtlebot3_localization_cpp
)
