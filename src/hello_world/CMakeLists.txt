cmake_minimum_required(VERSION 2.8.3)
project(hello_world)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package()

include_directories(
 include ${catkin_INCLUDE_DIRS}
)

add_executable(
	hello-world
	src/hello_world_node.cpp
)
target_link_libraries(
	hello-world
	${catkin_LIBRARIES}
)
add_dependencies(
	hello-world
	hello_world_cpp
)
