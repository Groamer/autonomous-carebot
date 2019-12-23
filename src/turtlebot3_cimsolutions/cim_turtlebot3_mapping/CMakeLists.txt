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

#Listener
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

#Publisher
add_executable(
	cim_turtlebot3_mapping_publisher
	src/PublisherApp.cpp
	src/MapPublisher.cpp
	src/MapIO.cpp
)
target_link_libraries(
	cim_turtlebot3_mapping_publisher
	${catkin_LIBRARIES}
)
add_dependencies(
	cim_turtlebot3_mapping_publisher
	cim_turtlebot3_mapping_publisher_cpp
)

#Launcher
add_executable(
	cim_turtlebot3_mapping_launcher
	src/LauncherApp.cpp
	src/MapLauncher.cpp
)
target_link_libraries(
	cim_turtlebot3_mapping_launcher
	${catkin_LIBRARIES}
)
add_dependencies(
	cim_turtlebot3_mapping_launcher
	cim_turtlebot3_mapping_launcher_cpp
)
