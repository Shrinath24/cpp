# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ec2-user/grpc/examples/cpp/route_guide

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/route_guide_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/route_guide_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/route_guide_server.dir/flags.make

route_guide.pb.cc: /home/ec2-user/grpc/examples/protos/route_guide.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating route_guide.pb.cc, route_guide.pb.h, route_guide.grpc.pb.cc, route_guide.grpc.pb.h"
	/home/ec2-user/local/bin/protoc-3.11.2.0 --grpc_out /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build --cpp_out /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build -I /home/ec2-user/grpc/examples/protos --plugin=protoc-gen-grpc="/home/ec2-user/local/bin/grpc_cpp_plugin" /home/ec2-user/grpc/examples/protos/route_guide.proto

route_guide.pb.h: route_guide.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate route_guide.pb.h

route_guide.grpc.pb.cc: route_guide.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate route_guide.grpc.pb.cc

route_guide.grpc.pb.h: route_guide.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate route_guide.grpc.pb.h

CMakeFiles/route_guide_server.dir/route_guide_server.cc.o: CMakeFiles/route_guide_server.dir/flags.make
CMakeFiles/route_guide_server.dir/route_guide_server.cc.o: ../../route_guide_server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/route_guide_server.dir/route_guide_server.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/route_guide_server.dir/route_guide_server.cc.o -c /home/ec2-user/grpc/examples/cpp/route_guide/route_guide_server.cc

CMakeFiles/route_guide_server.dir/route_guide_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/route_guide_server.dir/route_guide_server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ec2-user/grpc/examples/cpp/route_guide/route_guide_server.cc > CMakeFiles/route_guide_server.dir/route_guide_server.cc.i

CMakeFiles/route_guide_server.dir/route_guide_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/route_guide_server.dir/route_guide_server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ec2-user/grpc/examples/cpp/route_guide/route_guide_server.cc -o CMakeFiles/route_guide_server.dir/route_guide_server.cc.s

CMakeFiles/route_guide_server.dir/route_guide.pb.cc.o: CMakeFiles/route_guide_server.dir/flags.make
CMakeFiles/route_guide_server.dir/route_guide.pb.cc.o: route_guide.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/route_guide_server.dir/route_guide.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/route_guide_server.dir/route_guide.pb.cc.o -c /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/route_guide.pb.cc

CMakeFiles/route_guide_server.dir/route_guide.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/route_guide_server.dir/route_guide.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/route_guide.pb.cc > CMakeFiles/route_guide_server.dir/route_guide.pb.cc.i

CMakeFiles/route_guide_server.dir/route_guide.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/route_guide_server.dir/route_guide.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/route_guide.pb.cc -o CMakeFiles/route_guide_server.dir/route_guide.pb.cc.s

CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.o: CMakeFiles/route_guide_server.dir/flags.make
CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.o: route_guide.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.o -c /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/route_guide.grpc.pb.cc

CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/route_guide.grpc.pb.cc > CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.i

CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/route_guide.grpc.pb.cc -o CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.s

# Object files for target route_guide_server
route_guide_server_OBJECTS = \
"CMakeFiles/route_guide_server.dir/route_guide_server.cc.o" \
"CMakeFiles/route_guide_server.dir/route_guide.pb.cc.o" \
"CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.o"

# External object files for target route_guide_server
route_guide_server_EXTERNAL_OBJECTS =

route_guide_server: CMakeFiles/route_guide_server.dir/route_guide_server.cc.o
route_guide_server: CMakeFiles/route_guide_server.dir/route_guide.pb.cc.o
route_guide_server: CMakeFiles/route_guide_server.dir/route_guide.grpc.pb.cc.o
route_guide_server: CMakeFiles/route_guide_server.dir/build.make
route_guide_server: /home/ec2-user/local/lib/libgrpc++_reflection.a
route_guide_server: /home/ec2-user/local/lib/libgrpc++.a
route_guide_server: /home/ec2-user/local/lib64/libprotobuf.a
route_guide_server: /home/ec2-user/local/lib/libgrpc.a
route_guide_server: /home/ec2-user/local/lib/libssl.a
route_guide_server: /home/ec2-user/local/lib/libcrypto.a
route_guide_server: /home/ec2-user/local/lib/libgpr.a
route_guide_server: /home/ec2-user/local/lib/libabsl_str_format_internal.a
route_guide_server: /home/ec2-user/local/lib/libabsl_strings.a
route_guide_server: /home/ec2-user/local/lib/libabsl_throw_delegate.a
route_guide_server: /home/ec2-user/local/lib/libabsl_strings_internal.a
route_guide_server: /home/ec2-user/local/lib/libabsl_base.a
route_guide_server: /home/ec2-user/local/lib/libabsl_dynamic_annotations.a
route_guide_server: /home/ec2-user/local/lib/libabsl_spinlock_wait.a
route_guide_server: /usr/lib64/librt.so
route_guide_server: /home/ec2-user/local/lib/libabsl_int128.a
route_guide_server: /home/ec2-user/local/lib/libabsl_bad_optional_access.a
route_guide_server: /home/ec2-user/local/lib/libabsl_raw_logging_internal.a
route_guide_server: /home/ec2-user/local/lib/libabsl_log_severity.a
route_guide_server: /home/ec2-user/local/lib/libupb.a
route_guide_server: /home/ec2-user/local/lib/libz.a
route_guide_server: /home/ec2-user/local/lib/libcares.a
route_guide_server: /home/ec2-user/local/lib/libaddress_sorting.a
route_guide_server: CMakeFiles/route_guide_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable route_guide_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/route_guide_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/route_guide_server.dir/build: route_guide_server

.PHONY : CMakeFiles/route_guide_server.dir/build

CMakeFiles/route_guide_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/route_guide_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/route_guide_server.dir/clean

CMakeFiles/route_guide_server.dir/depend: route_guide.pb.cc
CMakeFiles/route_guide_server.dir/depend: route_guide.pb.h
CMakeFiles/route_guide_server.dir/depend: route_guide.grpc.pb.cc
CMakeFiles/route_guide_server.dir/depend: route_guide.grpc.pb.h
	cd /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ec2-user/grpc/examples/cpp/route_guide /home/ec2-user/grpc/examples/cpp/route_guide /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/CMakeFiles/route_guide_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/route_guide_server.dir/depend

