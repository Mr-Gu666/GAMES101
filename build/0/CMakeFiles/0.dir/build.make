# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = D:\interesting\GAMES101

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\interesting\GAMES101\build

# Include any dependencies generated for this target.
include 0/CMakeFiles/0.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include 0/CMakeFiles/0.dir/compiler_depend.make

# Include the progress variables for this target.
include 0/CMakeFiles/0.dir/progress.make

# Include the compile flags for this target's objects.
include 0/CMakeFiles/0.dir/flags.make

0/CMakeFiles/0.dir/main.cpp.obj: 0/CMakeFiles/0.dir/flags.make
0/CMakeFiles/0.dir/main.cpp.obj: 0/CMakeFiles/0.dir/includes_CXX.rsp
0/CMakeFiles/0.dir/main.cpp.obj: ../0/main.cpp
0/CMakeFiles/0.dir/main.cpp.obj: 0/CMakeFiles/0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\interesting\GAMES101\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 0/CMakeFiles/0.dir/main.cpp.obj"
	cd /d D:\interesting\GAMES101\build\0 && C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 0/CMakeFiles/0.dir/main.cpp.obj -MF CMakeFiles\0.dir\main.cpp.obj.d -o CMakeFiles\0.dir\main.cpp.obj -c D:\interesting\GAMES101\0\main.cpp

0/CMakeFiles/0.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0.dir/main.cpp.i"
	cd /d D:\interesting\GAMES101\build\0 && C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\interesting\GAMES101\0\main.cpp > CMakeFiles\0.dir\main.cpp.i

0/CMakeFiles/0.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0.dir/main.cpp.s"
	cd /d D:\interesting\GAMES101\build\0 && C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\interesting\GAMES101\0\main.cpp -o CMakeFiles\0.dir\main.cpp.s

# Object files for target 0
0_OBJECTS = \
"CMakeFiles/0.dir/main.cpp.obj"

# External object files for target 0
0_EXTERNAL_OBJECTS =

bin/0/0.exe: 0/CMakeFiles/0.dir/main.cpp.obj
bin/0/0.exe: 0/CMakeFiles/0.dir/build.make
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_gapi451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_highgui451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_ml451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_objdetect451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_photo451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_stitching451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_video451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_videoio451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_dnn451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_imgcodecs451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_calib3d451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_features2d451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_flann451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_imgproc451.dll.a
bin/0/0.exe: C:/opencv/build/x64/mingw/lib/libopencv_core451.dll.a
bin/0/0.exe: 0/CMakeFiles/0.dir/linklibs.rsp
bin/0/0.exe: 0/CMakeFiles/0.dir/objects1.rsp
bin/0/0.exe: 0/CMakeFiles/0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\interesting\GAMES101\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\0\0.exe"
	cd /d D:\interesting\GAMES101\build\0 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\0.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
0/CMakeFiles/0.dir/build: bin/0/0.exe
.PHONY : 0/CMakeFiles/0.dir/build

0/CMakeFiles/0.dir/clean:
	cd /d D:\interesting\GAMES101\build\0 && $(CMAKE_COMMAND) -P CMakeFiles\0.dir\cmake_clean.cmake
.PHONY : 0/CMakeFiles/0.dir/clean

0/CMakeFiles/0.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\interesting\GAMES101 D:\interesting\GAMES101\0 D:\interesting\GAMES101\build D:\interesting\GAMES101\build\0 D:\interesting\GAMES101\build\0\CMakeFiles\0.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : 0/CMakeFiles/0.dir/depend

