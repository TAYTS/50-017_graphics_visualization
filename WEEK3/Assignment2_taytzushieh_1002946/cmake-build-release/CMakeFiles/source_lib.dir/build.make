# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/source_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/source_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/source_lib.dir/flags.make

CMakeFiles/source_lib.dir/src/Matrix2f.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/Matrix2f.cpp.o: ../src/Matrix2f.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/source_lib.dir/src/Matrix2f.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/Matrix2f.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix2f.cpp

CMakeFiles/source_lib.dir/src/Matrix2f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/Matrix2f.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix2f.cpp > CMakeFiles/source_lib.dir/src/Matrix2f.cpp.i

CMakeFiles/source_lib.dir/src/Matrix2f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/Matrix2f.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix2f.cpp -o CMakeFiles/source_lib.dir/src/Matrix2f.cpp.s

CMakeFiles/source_lib.dir/src/Matrix3f.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/Matrix3f.cpp.o: ../src/Matrix3f.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/source_lib.dir/src/Matrix3f.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/Matrix3f.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix3f.cpp

CMakeFiles/source_lib.dir/src/Matrix3f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/Matrix3f.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix3f.cpp > CMakeFiles/source_lib.dir/src/Matrix3f.cpp.i

CMakeFiles/source_lib.dir/src/Matrix3f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/Matrix3f.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix3f.cpp -o CMakeFiles/source_lib.dir/src/Matrix3f.cpp.s

CMakeFiles/source_lib.dir/src/Matrix4f.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/Matrix4f.cpp.o: ../src/Matrix4f.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/source_lib.dir/src/Matrix4f.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/Matrix4f.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix4f.cpp

CMakeFiles/source_lib.dir/src/Matrix4f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/Matrix4f.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix4f.cpp > CMakeFiles/source_lib.dir/src/Matrix4f.cpp.i

CMakeFiles/source_lib.dir/src/Matrix4f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/Matrix4f.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Matrix4f.cpp -o CMakeFiles/source_lib.dir/src/Matrix4f.cpp.s

CMakeFiles/source_lib.dir/src/Quat4f.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/Quat4f.cpp.o: ../src/Quat4f.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/source_lib.dir/src/Quat4f.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/Quat4f.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Quat4f.cpp

CMakeFiles/source_lib.dir/src/Quat4f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/Quat4f.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Quat4f.cpp > CMakeFiles/source_lib.dir/src/Quat4f.cpp.i

CMakeFiles/source_lib.dir/src/Quat4f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/Quat4f.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Quat4f.cpp -o CMakeFiles/source_lib.dir/src/Quat4f.cpp.s

CMakeFiles/source_lib.dir/src/Vector2f.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/Vector2f.cpp.o: ../src/Vector2f.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/source_lib.dir/src/Vector2f.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/Vector2f.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector2f.cpp

CMakeFiles/source_lib.dir/src/Vector2f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/Vector2f.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector2f.cpp > CMakeFiles/source_lib.dir/src/Vector2f.cpp.i

CMakeFiles/source_lib.dir/src/Vector2f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/Vector2f.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector2f.cpp -o CMakeFiles/source_lib.dir/src/Vector2f.cpp.s

CMakeFiles/source_lib.dir/src/Vector3f.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/Vector3f.cpp.o: ../src/Vector3f.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/source_lib.dir/src/Vector3f.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/Vector3f.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector3f.cpp

CMakeFiles/source_lib.dir/src/Vector3f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/Vector3f.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector3f.cpp > CMakeFiles/source_lib.dir/src/Vector3f.cpp.i

CMakeFiles/source_lib.dir/src/Vector3f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/Vector3f.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector3f.cpp -o CMakeFiles/source_lib.dir/src/Vector3f.cpp.s

CMakeFiles/source_lib.dir/src/Vector4f.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/Vector4f.cpp.o: ../src/Vector4f.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/source_lib.dir/src/Vector4f.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/Vector4f.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector4f.cpp

CMakeFiles/source_lib.dir/src/Vector4f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/Vector4f.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector4f.cpp > CMakeFiles/source_lib.dir/src/Vector4f.cpp.i

CMakeFiles/source_lib.dir/src/Vector4f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/Vector4f.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/Vector4f.cpp -o CMakeFiles/source_lib.dir/src/Vector4f.cpp.s

CMakeFiles/source_lib.dir/src/curve.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/curve.cpp.o: ../src/curve.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/source_lib.dir/src/curve.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/curve.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/curve.cpp

CMakeFiles/source_lib.dir/src/curve.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/curve.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/curve.cpp > CMakeFiles/source_lib.dir/src/curve.cpp.i

CMakeFiles/source_lib.dir/src/curve.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/curve.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/curve.cpp -o CMakeFiles/source_lib.dir/src/curve.cpp.s

CMakeFiles/source_lib.dir/src/main.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/source_lib.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/main.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/main.cpp

CMakeFiles/source_lib.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/main.cpp > CMakeFiles/source_lib.dir/src/main.cpp.i

CMakeFiles/source_lib.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/main.cpp -o CMakeFiles/source_lib.dir/src/main.cpp.s

CMakeFiles/source_lib.dir/src/parse.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/parse.cpp.o: ../src/parse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/source_lib.dir/src/parse.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/parse.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/parse.cpp

CMakeFiles/source_lib.dir/src/parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/parse.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/parse.cpp > CMakeFiles/source_lib.dir/src/parse.cpp.i

CMakeFiles/source_lib.dir/src/parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/parse.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/parse.cpp -o CMakeFiles/source_lib.dir/src/parse.cpp.s

CMakeFiles/source_lib.dir/src/surf.cpp.o: CMakeFiles/source_lib.dir/flags.make
CMakeFiles/source_lib.dir/src/surf.cpp.o: ../src/surf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/source_lib.dir/src/surf.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source_lib.dir/src/surf.cpp.o -c /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/surf.cpp

CMakeFiles/source_lib.dir/src/surf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source_lib.dir/src/surf.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/surf.cpp > CMakeFiles/source_lib.dir/src/surf.cpp.i

CMakeFiles/source_lib.dir/src/surf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source_lib.dir/src/surf.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/src/surf.cpp -o CMakeFiles/source_lib.dir/src/surf.cpp.s

# Object files for target source_lib
source_lib_OBJECTS = \
"CMakeFiles/source_lib.dir/src/Matrix2f.cpp.o" \
"CMakeFiles/source_lib.dir/src/Matrix3f.cpp.o" \
"CMakeFiles/source_lib.dir/src/Matrix4f.cpp.o" \
"CMakeFiles/source_lib.dir/src/Quat4f.cpp.o" \
"CMakeFiles/source_lib.dir/src/Vector2f.cpp.o" \
"CMakeFiles/source_lib.dir/src/Vector3f.cpp.o" \
"CMakeFiles/source_lib.dir/src/Vector4f.cpp.o" \
"CMakeFiles/source_lib.dir/src/curve.cpp.o" \
"CMakeFiles/source_lib.dir/src/main.cpp.o" \
"CMakeFiles/source_lib.dir/src/parse.cpp.o" \
"CMakeFiles/source_lib.dir/src/surf.cpp.o"

# External object files for target source_lib
source_lib_EXTERNAL_OBJECTS =

libsource_lib.a: CMakeFiles/source_lib.dir/src/Matrix2f.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/Matrix3f.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/Matrix4f.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/Quat4f.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/Vector2f.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/Vector3f.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/Vector4f.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/curve.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/main.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/parse.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/src/surf.cpp.o
libsource_lib.a: CMakeFiles/source_lib.dir/build.make
libsource_lib.a: CMakeFiles/source_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libsource_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/source_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/source_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/source_lib.dir/build: libsource_lib.a

.PHONY : CMakeFiles/source_lib.dir/build

CMakeFiles/source_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/source_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/source_lib.dir/clean

CMakeFiles/source_lib.dir/depend:
	cd /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release /Users/mason/Desktop/Assignment_2/Assignment_1_NewFramework/cmake-build-release/CMakeFiles/source_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/source_lib.dir/depend

