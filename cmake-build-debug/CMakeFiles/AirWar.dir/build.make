# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/jeanpaul/Programs/clion-2016.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/jeanpaul/Programs/clion-2016.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jeanpaul/ClionProjects/AirWar++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jeanpaul/ClionProjects/AirWar++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AirWar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AirWar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AirWar.dir/flags.make

CMakeFiles/AirWar.dir/main.cpp.o: CMakeFiles/AirWar.dir/flags.make
CMakeFiles/AirWar.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jeanpaul/ClionProjects/AirWar++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AirWar.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AirWar.dir/main.cpp.o -c /home/jeanpaul/ClionProjects/AirWar++/main.cpp

CMakeFiles/AirWar.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AirWar.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jeanpaul/ClionProjects/AirWar++/main.cpp > CMakeFiles/AirWar.dir/main.cpp.i

CMakeFiles/AirWar.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AirWar.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jeanpaul/ClionProjects/AirWar++/main.cpp -o CMakeFiles/AirWar.dir/main.cpp.s

CMakeFiles/AirWar.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/AirWar.dir/main.cpp.o.requires

CMakeFiles/AirWar.dir/main.cpp.o.provides: CMakeFiles/AirWar.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/AirWar.dir/build.make CMakeFiles/AirWar.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/AirWar.dir/main.cpp.o.provides

CMakeFiles/AirWar.dir/main.cpp.o.provides.build: CMakeFiles/AirWar.dir/main.cpp.o


# Object files for target AirWar
AirWar_OBJECTS = \
"CMakeFiles/AirWar.dir/main.cpp.o"

# External object files for target AirWar
AirWar_EXTERNAL_OBJECTS =

AirWar: CMakeFiles/AirWar.dir/main.cpp.o
AirWar: CMakeFiles/AirWar.dir/build.make
AirWar: CMakeFiles/AirWar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jeanpaul/ClionProjects/AirWar++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AirWar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AirWar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AirWar.dir/build: AirWar

.PHONY : CMakeFiles/AirWar.dir/build

CMakeFiles/AirWar.dir/requires: CMakeFiles/AirWar.dir/main.cpp.o.requires

.PHONY : CMakeFiles/AirWar.dir/requires

CMakeFiles/AirWar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AirWar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AirWar.dir/clean

CMakeFiles/AirWar.dir/depend:
	cd /home/jeanpaul/ClionProjects/AirWar++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jeanpaul/ClionProjects/AirWar++ /home/jeanpaul/ClionProjects/AirWar++ /home/jeanpaul/ClionProjects/AirWar++/cmake-build-debug /home/jeanpaul/ClionProjects/AirWar++/cmake-build-debug /home/jeanpaul/ClionProjects/AirWar++/cmake-build-debug/CMakeFiles/AirWar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AirWar.dir/depend

