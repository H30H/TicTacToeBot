# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/Grisha/AppData/Local/JetBrains/CLion2021.2/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Grisha/AppData/Local/JetBrains/CLion2021.2/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/cMake/untitled1/TicTacToeBot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release

# Include any dependencies generated for this target.
include GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/depend.make
# Include the progress variables for this target.
include GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/progress.make

# Include the compile flags for this target's objects.
include GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/flags.make

GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/flags.make
GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: ../GoogleTests/googletests/googletest/src/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"
	cd /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.o -c /cygdrive/c/cMake/untitled1/TicTacToeBot/GoogleTests/googletests/googletest/src/gtest_main.cc

GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/cMake/untitled1/TicTacToeBot/GoogleTests/googletests/googletest/src/gtest_main.cc > CMakeFiles/gtest_main.dir/src/gtest_main.cc.i

GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/cMake/untitled1/TicTacToeBot/GoogleTests/googletests/googletest/src/gtest_main.cc -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.s

# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

lib/libgtest_main.a: GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
lib/libgtest_main.a: GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/build.make
lib/libgtest_main.a: GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libgtest_main.a"
	cd /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean_target.cmake
	cd /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/build: lib/libgtest_main.a
.PHONY : GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/build

GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/clean:
	cd /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean.cmake
.PHONY : GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/clean

GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/depend:
	cd /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/cMake/untitled1/TicTacToeBot /cygdrive/c/cMake/untitled1/TicTacToeBot/GoogleTests/googletests/googletest /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest /cygdrive/c/cMake/untitled1/TicTacToeBot/cmake-build-release/GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : GoogleTests/googletests/googletest/CMakeFiles/gtest_main.dir/depend

