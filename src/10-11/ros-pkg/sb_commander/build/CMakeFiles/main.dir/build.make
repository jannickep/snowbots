# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mark/snowbots/src/10-11/ros-pkg/sb_commander

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/main.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.o: ../src/main.cpp
CMakeFiles/main.dir/src/main.o: ../manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/ros/tools/rospack/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/ros/core/roslib/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/messages/std_msgs/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/messages/rosgraph_msgs/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/ros/core/rosbuild/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/ros/core/roslang/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/clients/rospy/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/utilities/cpp_common/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_traits/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/utilities/rostime/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_serialization/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/utilities/xmlrpcpp/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rosconsole/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/ros/tools/rosclean/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rosgraph/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rosparam/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rosmaster/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rosout/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/roslaunch/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/ros/tools/rosunit/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rostest/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/topic_tools/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rosbag/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/rosbagmigration/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/common_msgs/geometry_msgs/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/common_msgs/sensor_msgs/manifest.xml
CMakeFiles/main.dir/src/main.o: /home/mark/snowbots/src/10-11/ros-pkg/sb_msgs/manifest.xml
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/messages/std_msgs/msg_gen/generated
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/messages/rosgraph_msgs/msg_gen/generated
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp/msg_gen/generated
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp/srv_gen/generated
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/ros_comm/tools/topic_tools/srv_gen/generated
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/common_msgs/geometry_msgs/msg_gen/generated
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/common_msgs/sensor_msgs/msg_gen/generated
CMakeFiles/main.dir/src/main.o: /opt/ros/electric/stacks/common_msgs/sensor_msgs/srv_gen/generated
CMakeFiles/main.dir/src/main.o: /home/mark/snowbots/src/10-11/ros-pkg/sb_msgs/msg_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/src/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/main.dir/src/main.o -c /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/src/main.cpp

CMakeFiles/main.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/src/main.cpp > CMakeFiles/main.dir/src/main.i

CMakeFiles/main.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/src/main.cpp -o CMakeFiles/main.dir/src/main.s

CMakeFiles/main.dir/src/main.o.requires:
.PHONY : CMakeFiles/main.dir/src/main.o.requires

CMakeFiles/main.dir/src/main.o.provides: CMakeFiles/main.dir/src/main.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.o.provides.build
.PHONY : CMakeFiles/main.dir/src/main.o.provides

CMakeFiles/main.dir/src/main.o.provides.build: CMakeFiles/main.dir/src/main.o

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/main.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

../bin/main: CMakeFiles/main.dir/src/main.o
../bin/main: ../lib/libsb_commander.so
../bin/main: CMakeFiles/main.dir/build.make
../bin/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: ../bin/main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/main.o.requires
.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/snowbots/src/10-11/ros-pkg/sb_commander /home/mark/snowbots/src/10-11/ros-pkg/sb_commander /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/build /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/build /home/mark/snowbots/src/10-11/ros-pkg/sb_commander/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

