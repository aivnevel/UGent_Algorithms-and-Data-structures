# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.0_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.0_1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/build

# Include any dependencies generated for this target.
include CMakeFiles/exthash.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exthash.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exthash.dir/flags.make

CMakeFiles/exthash.dir/src/main.cpp.o: CMakeFiles/exthash.dir/flags.make
CMakeFiles/exthash.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exthash.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exthash.dir/src/main.cpp.o -c /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/src/main.cpp

CMakeFiles/exthash.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exthash.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/src/main.cpp > CMakeFiles/exthash.dir/src/main.cpp.i

CMakeFiles/exthash.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exthash.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/src/main.cpp -o CMakeFiles/exthash.dir/src/main.cpp.s

# Object files for target exthash
exthash_OBJECTS = \
"CMakeFiles/exthash.dir/src/main.cpp.o"

# External object files for target exthash
exthash_EXTERNAL_OBJECTS =

exthash: CMakeFiles/exthash.dir/src/main.cpp.o
exthash: CMakeFiles/exthash.dir/build.make
exthash: libexthashlib.dylib
exthash: CMakeFiles/exthash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exthash"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exthash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exthash.dir/build: exthash

.PHONY : CMakeFiles/exthash.dir/build

CMakeFiles/exthash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exthash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exthash.dir/clean

CMakeFiles/exthash.dir/depend:
	cd /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/build /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/build /Users/alexandervannevel/Documents/GevAlExamen1-aivnevel/build/CMakeFiles/exthash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exthash.dir/depend

