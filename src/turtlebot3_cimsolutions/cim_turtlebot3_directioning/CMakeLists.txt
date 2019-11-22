cmake_minimum_required(VERSION 2.8.3)
project(cim_turtlebot3_directioning)

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
	cim_turtlebot3_directioning
	src/DirectioningApp.cpp
	src/EulerAnglesConverter.cpp
	src/DegreesConverter.cpp
)
target_link_libraries(
	cim_turtlebot3_directioning
	${catkin_LIBRARIES}
)
add_dependencies(
	cim_turtlebot3_directioning
	cim_turtlebot3_directioning_cpp
)
