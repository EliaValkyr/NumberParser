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


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/elia/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.8194.17/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/elia/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.8194.17/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/elia/CLionProjects/NumberParser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/elia/CLionProjects/NumberParser/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NumberParser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NumberParser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NumberParser.dir/flags.make

CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.o: CMakeFiles/NumberParser.dir/flags.make
CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.o: ../NumberParser/number_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elia/CLionProjects/NumberParser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.o -c /home/elia/CLionProjects/NumberParser/NumberParser/number_parser.cpp

CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/elia/CLionProjects/NumberParser/NumberParser/number_parser.cpp > CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.i

CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/elia/CLionProjects/NumberParser/NumberParser/number_parser.cpp -o CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.s

CMakeFiles/NumberParser.dir/main.cpp.o: CMakeFiles/NumberParser.dir/flags.make
CMakeFiles/NumberParser.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elia/CLionProjects/NumberParser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NumberParser.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NumberParser.dir/main.cpp.o -c /home/elia/CLionProjects/NumberParser/main.cpp

CMakeFiles/NumberParser.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NumberParser.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/elia/CLionProjects/NumberParser/main.cpp > CMakeFiles/NumberParser.dir/main.cpp.i

CMakeFiles/NumberParser.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NumberParser.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/elia/CLionProjects/NumberParser/main.cpp -o CMakeFiles/NumberParser.dir/main.cpp.s

# Object files for target NumberParser
NumberParser_OBJECTS = \
"CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.o" \
"CMakeFiles/NumberParser.dir/main.cpp.o"

# External object files for target NumberParser
NumberParser_EXTERNAL_OBJECTS =

libNumberParser.a: CMakeFiles/NumberParser.dir/NumberParser/number_parser.cpp.o
libNumberParser.a: CMakeFiles/NumberParser.dir/main.cpp.o
libNumberParser.a: CMakeFiles/NumberParser.dir/build.make
libNumberParser.a: CMakeFiles/NumberParser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elia/CLionProjects/NumberParser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libNumberParser.a"
	$(CMAKE_COMMAND) -P CMakeFiles/NumberParser.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NumberParser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NumberParser.dir/build: libNumberParser.a

.PHONY : CMakeFiles/NumberParser.dir/build

CMakeFiles/NumberParser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NumberParser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NumberParser.dir/clean

CMakeFiles/NumberParser.dir/depend:
	cd /home/elia/CLionProjects/NumberParser/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elia/CLionProjects/NumberParser /home/elia/CLionProjects/NumberParser /home/elia/CLionProjects/NumberParser/cmake-build-debug /home/elia/CLionProjects/NumberParser/cmake-build-debug /home/elia/CLionProjects/NumberParser/cmake-build-debug/CMakeFiles/NumberParser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NumberParser.dir/depend
