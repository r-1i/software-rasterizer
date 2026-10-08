	# CMakeList.txt : CMake project for SoftwareRasterizer, include source and define
	# project specific logic here.
	#
	cmake_minimum_required (VERSION 3.25)
	
	# Enable Hot Reload for MSVC compilers if supported.
	if (POLICY CMP0141)
	  cmake_policy(SET CMP0141 NEW)
	  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<CXX_COMPILER_ID:MSVC>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
	endif()

	project (SoftwareRasterizer LANGUAGES CXX)
	
	# Add source to this project's executable.
	add_executable (SoftwareRasterizer "src/SoftwareRasterizer.cpp" "src/SoftwareRasterizer.h")

	set_property(TARGET SoftwareRasterizer PROPERTY CXX_STANDARD 20)
	set_property(TARGET SoftwareRasterizer PROPERTY CXX_STANDARD_REQUIRED ON)

	target_include_directories(SoftwareRasterizer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
	target_include_directories(SoftwareRasterizer SYSTEM PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/")


