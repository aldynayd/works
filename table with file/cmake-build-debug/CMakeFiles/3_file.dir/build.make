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
CMAKE_SOURCE_DIR = "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/3_file.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/3_file.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3_file.dir/flags.make

CMakeFiles/3_file.dir/main.c.o: CMakeFiles/3_file.dir/flags.make
CMakeFiles/3_file.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/3_file.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/3_file.dir/main.c.o   -c "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/main.c"

CMakeFiles/3_file.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/3_file.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/main.c" > CMakeFiles/3_file.dir/main.c.i

CMakeFiles/3_file.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/3_file.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/main.c" -o CMakeFiles/3_file.dir/main.c.s

CMakeFiles/3_file.dir/table.c.o: CMakeFiles/3_file.dir/flags.make
CMakeFiles/3_file.dir/table.c.o: ../table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/3_file.dir/table.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/3_file.dir/table.c.o   -c "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/table.c"

CMakeFiles/3_file.dir/table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/3_file.dir/table.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/table.c" > CMakeFiles/3_file.dir/table.c.i

CMakeFiles/3_file.dir/table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/3_file.dir/table.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/table.c" -o CMakeFiles/3_file.dir/table.c.s

# Object files for target 3_file
3_file_OBJECTS = \
"CMakeFiles/3_file.dir/main.c.o" \
"CMakeFiles/3_file.dir/table.c.o"

# External object files for target 3_file
3_file_EXTERNAL_OBJECTS =

3_file: CMakeFiles/3_file.dir/main.c.o
3_file: CMakeFiles/3_file.dir/table.c.o
3_file: CMakeFiles/3_file.dir/build.make
3_file: CMakeFiles/3_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable 3_file"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3_file.dir/build: 3_file

.PHONY : CMakeFiles/3_file.dir/build

CMakeFiles/3_file.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3_file.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3_file.dir/clean

CMakeFiles/3_file.dir/depend:
	cd "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file" "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file" "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug" "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug" "/mnt/c/Users/darga/Documents/study/1.2 2022/3_file/cmake-build-debug/CMakeFiles/3_file.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/3_file.dir/depend

