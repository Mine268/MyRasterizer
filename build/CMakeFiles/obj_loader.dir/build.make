# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\work\MyRasterizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\work\MyRasterizer\build

# Include any dependencies generated for this target.
include CMakeFiles/obj_loader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/obj_loader.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/obj_loader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/obj_loader.dir/flags.make

CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj: CMakeFiles/obj_loader.dir/flags.make
CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj: CMakeFiles/obj_loader.dir/includes_CXX.rsp
CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj: D:/work/MyRasterizer/src/OBJ_loader.cpp
CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj: CMakeFiles/obj_loader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\work\MyRasterizer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj -MF CMakeFiles\obj_loader.dir\src\OBJ_loader.cpp.obj.d -o CMakeFiles\obj_loader.dir\src\OBJ_loader.cpp.obj -c D:\work\MyRasterizer\src\OBJ_loader.cpp

CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\work\MyRasterizer\src\OBJ_loader.cpp > CMakeFiles\obj_loader.dir\src\OBJ_loader.cpp.i

CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\work\MyRasterizer\src\OBJ_loader.cpp -o CMakeFiles\obj_loader.dir\src\OBJ_loader.cpp.s

# Object files for target obj_loader
obj_loader_OBJECTS = \
"CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj"

# External object files for target obj_loader
obj_loader_EXTERNAL_OBJECTS =

libobj_loader.a: CMakeFiles/obj_loader.dir/src/OBJ_loader.cpp.obj
libobj_loader.a: CMakeFiles/obj_loader.dir/build.make
libobj_loader.a: CMakeFiles/obj_loader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\work\MyRasterizer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libobj_loader.a"
	$(CMAKE_COMMAND) -P CMakeFiles\obj_loader.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\obj_loader.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/obj_loader.dir/build: libobj_loader.a
.PHONY : CMakeFiles/obj_loader.dir/build

CMakeFiles/obj_loader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\obj_loader.dir\cmake_clean.cmake
.PHONY : CMakeFiles/obj_loader.dir/clean

CMakeFiles/obj_loader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\work\MyRasterizer D:\work\MyRasterizer D:\work\MyRasterizer\build D:\work\MyRasterizer\build D:\work\MyRasterizer\build\CMakeFiles\obj_loader.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/obj_loader.dir/depend

