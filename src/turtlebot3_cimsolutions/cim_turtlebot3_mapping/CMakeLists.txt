cmake_minimum_required(VERSION 2.8.3)
project(cim_turtlebot3_mapping)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	genmsg
)

#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

#generate_messages(DEPENDENCIES std_msgs)

catkin_package()

include_directories(
	include ${catkin_INCLUDE_DIRS}
)

add_executable(
	cim_turtlebot3_mapping
	src/Program.cpp
	#src/MapListener.cpp
	#src/MapIO.cpp
)
target_link_libraries(
	cim_turtlebot3_mapping
	${catkin_LIBRARIES}
)
#add_dependencies(
#	cim_turtlebot3_mapping
#)
