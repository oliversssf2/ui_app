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
CMAKE_SOURCE_DIR = /home/min/workspace/ui_app

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/min/workspace/ui_app

# Utility rule file for application_autogen.

# Include the progress variables for this target.
include CMakeFiles/application_autogen.dir/progress.make

CMakeFiles/application_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/min/workspace/ui_app/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target application"
	/usr/local/bin/cmake -E cmake_autogen /home/min/workspace/ui_app/CMakeFiles/application_autogen.dir/AutogenInfo.cmake ""

application_autogen: CMakeFiles/application_autogen
application_autogen: CMakeFiles/application_autogen.dir/build.make

.PHONY : application_autogen

# Rule to build all files generated by this target.
CMakeFiles/application_autogen.dir/build: application_autogen

.PHONY : CMakeFiles/application_autogen.dir/build

CMakeFiles/application_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/application_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/application_autogen.dir/clean

CMakeFiles/application_autogen.dir/depend:
	cd /home/min/workspace/ui_app && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/min/workspace/ui_app /home/min/workspace/ui_app /home/min/workspace/ui_app /home/min/workspace/ui_app /home/min/workspace/ui_app/CMakeFiles/application_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/application_autogen.dir/depend

