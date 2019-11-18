cmake_minimum_required(VERSION 2.8.3)
project(cim_turtlebot3_mapping)

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
	cim_turtlebot3_mapping_listener
	src/ListenerApp.cpp
	src/MapListener.cpp
	src/MapIO.cpp
)
target_link_libraries(
	cim_turtlebot3_mapping_listener
	${catkin_LIBRARIES}
)
add_dependencies(
	cim_turtlebot3_mapping_listener
	cim_turtlebot3_mapping_listener_cpp
)

add_executable(
	cim_turtlebot3_mapping_provider
	src/ProviderApp.cpp
	src/MapProvider.cpp
	src/MapIO.cpp
)
target_link_libraries(
	cim_turtlebot3_mapping_provider
	${catkin_LIBRARIES}
)
add_dependencies(
	cim_turtlebot3_mapping_provider
	cim_turtlebot3_mapping_provider_cpp
)
