# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oscar/Compiladores3/MiniC++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oscar/Compiladores3/MiniC++/build

# Include any dependencies generated for this target.
include CMakeFiles/MiniC++.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MiniC++.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MiniC++.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MiniC++.dir/flags.make

LexerImpl.cpp: ../Lexer.re
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/oscar/Compiladores3/MiniC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating LexerImpl.cpp"
	re2c -o LexerImpl.cpp /home/oscar/Compiladores3/MiniC++/Lexer.re

CMakeFiles/MiniC++.dir/LexerImpl.cpp.o: CMakeFiles/MiniC++.dir/flags.make
CMakeFiles/MiniC++.dir/LexerImpl.cpp.o: LexerImpl.cpp
CMakeFiles/MiniC++.dir/LexerImpl.cpp.o: CMakeFiles/MiniC++.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oscar/Compiladores3/MiniC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MiniC++.dir/LexerImpl.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MiniC++.dir/LexerImpl.cpp.o -MF CMakeFiles/MiniC++.dir/LexerImpl.cpp.o.d -o CMakeFiles/MiniC++.dir/LexerImpl.cpp.o -c /home/oscar/Compiladores3/MiniC++/build/LexerImpl.cpp

CMakeFiles/MiniC++.dir/LexerImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniC++.dir/LexerImpl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oscar/Compiladores3/MiniC++/build/LexerImpl.cpp > CMakeFiles/MiniC++.dir/LexerImpl.cpp.i

CMakeFiles/MiniC++.dir/LexerImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniC++.dir/LexerImpl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oscar/Compiladores3/MiniC++/build/LexerImpl.cpp -o CMakeFiles/MiniC++.dir/LexerImpl.cpp.s

CMakeFiles/MiniC++.dir/main.cpp.o: CMakeFiles/MiniC++.dir/flags.make
CMakeFiles/MiniC++.dir/main.cpp.o: ../main.cpp
CMakeFiles/MiniC++.dir/main.cpp.o: CMakeFiles/MiniC++.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oscar/Compiladores3/MiniC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MiniC++.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MiniC++.dir/main.cpp.o -MF CMakeFiles/MiniC++.dir/main.cpp.o.d -o CMakeFiles/MiniC++.dir/main.cpp.o -c /home/oscar/Compiladores3/MiniC++/main.cpp

CMakeFiles/MiniC++.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniC++.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oscar/Compiladores3/MiniC++/main.cpp > CMakeFiles/MiniC++.dir/main.cpp.i

CMakeFiles/MiniC++.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniC++.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oscar/Compiladores3/MiniC++/main.cpp -o CMakeFiles/MiniC++.dir/main.cpp.s

CMakeFiles/MiniC++.dir/Parser.cpp.o: CMakeFiles/MiniC++.dir/flags.make
CMakeFiles/MiniC++.dir/Parser.cpp.o: ../Parser.cpp
CMakeFiles/MiniC++.dir/Parser.cpp.o: CMakeFiles/MiniC++.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oscar/Compiladores3/MiniC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MiniC++.dir/Parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MiniC++.dir/Parser.cpp.o -MF CMakeFiles/MiniC++.dir/Parser.cpp.o.d -o CMakeFiles/MiniC++.dir/Parser.cpp.o -c /home/oscar/Compiladores3/MiniC++/Parser.cpp

CMakeFiles/MiniC++.dir/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniC++.dir/Parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oscar/Compiladores3/MiniC++/Parser.cpp > CMakeFiles/MiniC++.dir/Parser.cpp.i

CMakeFiles/MiniC++.dir/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniC++.dir/Parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oscar/Compiladores3/MiniC++/Parser.cpp -o CMakeFiles/MiniC++.dir/Parser.cpp.s

CMakeFiles/MiniC++.dir/Ast.cpp.o: CMakeFiles/MiniC++.dir/flags.make
CMakeFiles/MiniC++.dir/Ast.cpp.o: ../Ast.cpp
CMakeFiles/MiniC++.dir/Ast.cpp.o: CMakeFiles/MiniC++.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oscar/Compiladores3/MiniC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MiniC++.dir/Ast.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MiniC++.dir/Ast.cpp.o -MF CMakeFiles/MiniC++.dir/Ast.cpp.o.d -o CMakeFiles/MiniC++.dir/Ast.cpp.o -c /home/oscar/Compiladores3/MiniC++/Ast.cpp

CMakeFiles/MiniC++.dir/Ast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniC++.dir/Ast.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oscar/Compiladores3/MiniC++/Ast.cpp > CMakeFiles/MiniC++.dir/Ast.cpp.i

CMakeFiles/MiniC++.dir/Ast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniC++.dir/Ast.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oscar/Compiladores3/MiniC++/Ast.cpp -o CMakeFiles/MiniC++.dir/Ast.cpp.s

CMakeFiles/MiniC++.dir/Generacion.cpp.o: CMakeFiles/MiniC++.dir/flags.make
CMakeFiles/MiniC++.dir/Generacion.cpp.o: ../Generacion.cpp
CMakeFiles/MiniC++.dir/Generacion.cpp.o: CMakeFiles/MiniC++.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oscar/Compiladores3/MiniC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MiniC++.dir/Generacion.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MiniC++.dir/Generacion.cpp.o -MF CMakeFiles/MiniC++.dir/Generacion.cpp.o.d -o CMakeFiles/MiniC++.dir/Generacion.cpp.o -c /home/oscar/Compiladores3/MiniC++/Generacion.cpp

CMakeFiles/MiniC++.dir/Generacion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniC++.dir/Generacion.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oscar/Compiladores3/MiniC++/Generacion.cpp > CMakeFiles/MiniC++.dir/Generacion.cpp.i

CMakeFiles/MiniC++.dir/Generacion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniC++.dir/Generacion.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oscar/Compiladores3/MiniC++/Generacion.cpp -o CMakeFiles/MiniC++.dir/Generacion.cpp.s

# Object files for target MiniC++
MiniC_______OBJECTS = \
"CMakeFiles/MiniC++.dir/LexerImpl.cpp.o" \
"CMakeFiles/MiniC++.dir/main.cpp.o" \
"CMakeFiles/MiniC++.dir/Parser.cpp.o" \
"CMakeFiles/MiniC++.dir/Ast.cpp.o" \
"CMakeFiles/MiniC++.dir/Generacion.cpp.o"

# External object files for target MiniC++
MiniC_______EXTERNAL_OBJECTS =

MiniC++: CMakeFiles/MiniC++.dir/LexerImpl.cpp.o
MiniC++: CMakeFiles/MiniC++.dir/main.cpp.o
MiniC++: CMakeFiles/MiniC++.dir/Parser.cpp.o
MiniC++: CMakeFiles/MiniC++.dir/Ast.cpp.o
MiniC++: CMakeFiles/MiniC++.dir/Generacion.cpp.o
MiniC++: CMakeFiles/MiniC++.dir/build.make
MiniC++: CMakeFiles/MiniC++.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oscar/Compiladores3/MiniC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable MiniC++"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MiniC++.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MiniC++.dir/build: MiniC++
.PHONY : CMakeFiles/MiniC++.dir/build

CMakeFiles/MiniC++.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MiniC++.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MiniC++.dir/clean

CMakeFiles/MiniC++.dir/depend: LexerImpl.cpp
	cd /home/oscar/Compiladores3/MiniC++/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oscar/Compiladores3/MiniC++ /home/oscar/Compiladores3/MiniC++ /home/oscar/Compiladores3/MiniC++/build /home/oscar/Compiladores3/MiniC++/build /home/oscar/Compiladores3/MiniC++/build/CMakeFiles/MiniC++.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MiniC++.dir/depend

