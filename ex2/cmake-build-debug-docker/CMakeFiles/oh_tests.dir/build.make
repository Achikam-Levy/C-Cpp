# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.gUXVI4E7TS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker

# Include any dependencies generated for this target.
include CMakeFiles/oh_tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/oh_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oh_tests.dir/flags.make

CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.o: CMakeFiles/oh_tests.dir/flags.make
CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.o: ../oh_tests/oh_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.o   -c /tmp/tmp.gUXVI4E7TS/oh_tests/oh_tests.c

CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.gUXVI4E7TS/oh_tests/oh_tests.c > CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.i

CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.gUXVI4E7TS/oh_tests/oh_tests.c -o CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.s

CMakeFiles/oh_tests.dir/ProductBST.c.o: CMakeFiles/oh_tests.dir/flags.make
CMakeFiles/oh_tests.dir/ProductBST.c.o: ../ProductBST.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/oh_tests.dir/ProductBST.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/oh_tests.dir/ProductBST.c.o   -c /tmp/tmp.gUXVI4E7TS/ProductBST.c

CMakeFiles/oh_tests.dir/ProductBST.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/oh_tests.dir/ProductBST.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.gUXVI4E7TS/ProductBST.c > CMakeFiles/oh_tests.dir/ProductBST.c.i

CMakeFiles/oh_tests.dir/ProductBST.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/oh_tests.dir/ProductBST.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.gUXVI4E7TS/ProductBST.c -o CMakeFiles/oh_tests.dir/ProductBST.c.s

CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.o: CMakeFiles/oh_tests.dir/flags.make
CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.o: ../oh_tests/oh_tests_helpers.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.o   -c /tmp/tmp.gUXVI4E7TS/oh_tests/oh_tests_helpers.c

CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.gUXVI4E7TS/oh_tests/oh_tests_helpers.c > CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.i

CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.gUXVI4E7TS/oh_tests/oh_tests_helpers.c -o CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.s

# Object files for target oh_tests
oh_tests_OBJECTS = \
"CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.o" \
"CMakeFiles/oh_tests.dir/ProductBST.c.o" \
"CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.o"

# External object files for target oh_tests
oh_tests_EXTERNAL_OBJECTS =

oh_tests: CMakeFiles/oh_tests.dir/oh_tests/oh_tests.c.o
oh_tests: CMakeFiles/oh_tests.dir/ProductBST.c.o
oh_tests: CMakeFiles/oh_tests.dir/oh_tests/oh_tests_helpers.c.o
oh_tests: CMakeFiles/oh_tests.dir/build.make
oh_tests: CMakeFiles/oh_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable oh_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oh_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oh_tests.dir/build: oh_tests

.PHONY : CMakeFiles/oh_tests.dir/build

CMakeFiles/oh_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/oh_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/oh_tests.dir/clean

CMakeFiles/oh_tests.dir/depend:
	cd /tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.gUXVI4E7TS /tmp/tmp.gUXVI4E7TS /tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker /tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker /tmp/tmp.gUXVI4E7TS/cmake-build-debug-docker/CMakeFiles/oh_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/oh_tests.dir/depend
