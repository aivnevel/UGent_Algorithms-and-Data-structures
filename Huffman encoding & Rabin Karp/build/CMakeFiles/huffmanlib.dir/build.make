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
CMAKE_SOURCE_DIR = /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/build

# Include any dependencies generated for this target.
include CMakeFiles/huffmanlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/huffmanlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/huffmanlib.dir/flags.make

CMakeFiles/huffmanlib.dir/src/huffman.cpp.o: CMakeFiles/huffmanlib.dir/flags.make
CMakeFiles/huffmanlib.dir/src/huffman.cpp.o: ../src/huffman.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/huffmanlib.dir/src/huffman.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/huffmanlib.dir/src/huffman.cpp.o -c /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/src/huffman.cpp

CMakeFiles/huffmanlib.dir/src/huffman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/huffmanlib.dir/src/huffman.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/src/huffman.cpp > CMakeFiles/huffmanlib.dir/src/huffman.cpp.i

CMakeFiles/huffmanlib.dir/src/huffman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/huffmanlib.dir/src/huffman.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/src/huffman.cpp -o CMakeFiles/huffmanlib.dir/src/huffman.cpp.s

# Object files for target huffmanlib
huffmanlib_OBJECTS = \
"CMakeFiles/huffmanlib.dir/src/huffman.cpp.o"

# External object files for target huffmanlib
huffmanlib_EXTERNAL_OBJECTS =

libhuffmanlib.dylib: CMakeFiles/huffmanlib.dir/src/huffman.cpp.o
libhuffmanlib.dylib: CMakeFiles/huffmanlib.dir/build.make
libhuffmanlib.dylib: CMakeFiles/huffmanlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libhuffmanlib.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/huffmanlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/huffmanlib.dir/build: libhuffmanlib.dylib

.PHONY : CMakeFiles/huffmanlib.dir/build

CMakeFiles/huffmanlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/huffmanlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/huffmanlib.dir/clean

CMakeFiles/huffmanlib.dir/depend:
	cd /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/build /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/build /Users/alexandervannevel/Documents/testalgo/GevAlTest2-aivnevel/build/CMakeFiles/huffmanlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/huffmanlib.dir/depend

