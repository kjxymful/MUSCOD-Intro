# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/build

# Include any dependencies generated for this target.
include CMakeFiles/hoppingrobot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hoppingrobot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hoppingrobot.dir/flags.make

CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.o: CMakeFiles/hoppingrobot.dir/flags.make
CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.o: ../SRC/hoppingrobot.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.o -c /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/SRC/hoppingrobot.cc

CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/SRC/hoppingrobot.cc > CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.i

CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/SRC/hoppingrobot.cc -o CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.s

# Object files for target hoppingrobot
hoppingrobot_OBJECTS = \
"CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.o"

# External object files for target hoppingrobot
hoppingrobot_EXTERNAL_OBJECTS =

libhoppingrobot.so: CMakeFiles/hoppingrobot.dir/SRC/hoppingrobot.cc.o
libhoppingrobot.so: CMakeFiles/hoppingrobot.dir/build.make
libhoppingrobot.so: /usr/local/lib/librbdl.so
libhoppingrobot.so: /usr/local/lib/librbdl_luamodel.so
libhoppingrobot.so: /usr/local/lib/librbdl_luamodel.so
libhoppingrobot.so: CMakeFiles/hoppingrobot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libhoppingrobot.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hoppingrobot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hoppingrobot.dir/build: libhoppingrobot.so

.PHONY : CMakeFiles/hoppingrobot.dir/build

CMakeFiles/hoppingrobot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hoppingrobot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hoppingrobot.dir/clean

CMakeFiles/hoppingrobot.dir/depend:
	cd /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/build /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/build /home/patrick/Downloads/MUSCOD-Intro/hoppingRobot_template/build/CMakeFiles/hoppingrobot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hoppingrobot.dir/depend

