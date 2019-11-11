cmake_minimum_required(VERSION 2.8.3)
project(cim_turtlebot3_topic_tester)

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
	cim_turtlebot3_topic_tester
	src/Program.cpp
)
target_link_libraries(
	cim_turtlebot3_topic_tester
	${catkin_LIBRARIES}
)
