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
CMAKE_SOURCE_DIR = /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build

# Include any dependencies generated for this target.
include src/CMakeFiles/font.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/font.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/font.dir/flags.make

src/CMakeFiles/font.dir/font.cpp.o: src/CMakeFiles/font.dir/flags.make
src/CMakeFiles/font.dir/font.cpp.o: ../src/font.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/font.dir/font.cpp.o"
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/font.dir/font.cpp.o -c /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/src/font.cpp

src/CMakeFiles/font.dir/font.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/font.dir/font.cpp.i"
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/src/font.cpp > CMakeFiles/font.dir/font.cpp.i

src/CMakeFiles/font.dir/font.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/font.dir/font.cpp.s"
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/src/font.cpp -o CMakeFiles/font.dir/font.cpp.s

src/CMakeFiles/font.dir/truetype.cpp.o: src/CMakeFiles/font.dir/flags.make
src/CMakeFiles/font.dir/truetype.cpp.o: ../src/truetype.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/font.dir/truetype.cpp.o"
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/font.dir/truetype.cpp.o -c /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/src/truetype.cpp

src/CMakeFiles/font.dir/truetype.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/font.dir/truetype.cpp.i"
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/src/truetype.cpp > CMakeFiles/font.dir/truetype.cpp.i

src/CMakeFiles/font.dir/truetype.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/font.dir/truetype.cpp.s"
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/src/truetype.cpp -o CMakeFiles/font.dir/truetype.cpp.s

# Object files for target font
font_OBJECTS = \
"CMakeFiles/font.dir/font.cpp.o" \
"CMakeFiles/font.dir/truetype.cpp.o"

# External object files for target font
font_EXTERNAL_OBJECTS =

src/libfont.a: src/CMakeFiles/font.dir/font.cpp.o
src/libfont.a: src/CMakeFiles/font.dir/truetype.cpp.o
src/libfont.a: src/CMakeFiles/font.dir/build.make
src/libfont.a: src/CMakeFiles/font.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libfont.a"
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && $(CMAKE_COMMAND) -P CMakeFiles/font.dir/cmake_clean_target.cmake
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/font.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/font.dir/build: src/libfont.a

.PHONY : src/CMakeFiles/font.dir/build

src/CMakeFiles/font.dir/clean:
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src && $(CMAKE_COMMAND) -P CMakeFiles/font.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/font.dir/clean

src/CMakeFiles/font.dir/depend:
	cd /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/src /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src /mnt/hgfs/gongxiang/code/myproject/Stargazing_platform/stargazing_platform_program/build/src/CMakeFiles/font.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/font.dir/depend

