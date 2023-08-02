cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(circular 
  VERSION 0.1
  DESCRIPTION "idk"
  LANGUAGES CXX)

##########################
# Build type and details #
##########################

# we default to Release build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ flags, Debug configuration: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ flags, Release configuration: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "C++ flags, Release configuration with Debug info: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "C++ flags, minimal Release configuration: ${CMAKE_CXX_FLAGS_MINSIZEREL}")

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND feature_tokens "features")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Set -fPIC
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)

  # Nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    list(APPEND feature_tokens "docs")
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

include(FetchContent)

# Check if we can enable interprocedural optimization
include(CheckIPOSupported)

################
# Dependencies #
################

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(SourceLists)

# Register subdirectories
add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR CIRCULAR_BUILD_TESTING)
   AND BUILD_TESTING)
  list(APPEND feature_tokens "tests")
  add_subdirectory(tests)
endif()

################################
# Platform detection and setup #
################################

message(STATUS "Detecting platform...")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(STATUS "Configuring on/for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "Configuring on/for Windows")
else()
  message(FATAL_ERROR "CMAKE_SYSTEM_NAME is neither 'Linux' nor 'Windows'")
endif()

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-march=native" _march_native_works)
check_cxx_compiler_flag("-xHost" _xhost_works)

set(_CXX_FLAGS)
if(_march_native_works)
  message(STATUS "Using processor's vector instructions (-march=native compiler flag set)")
  list(APPEND feature_tokens "arch-native")
  set(_CXX_FLAGS "-march=native")
elseif(_xhost_works)
  message(STATUS "Using processor's vector instructions (-xHost compiler flag set)")
  list(APPEND feature_tokens "arch-xhost")
  set(_CXX_FLAGS "-xHost")
else()
  message(STATUS "No suitable compiler flag found for vectorization")
endif()

list(APPEND flags "-Wall")
if(NOT WIN32)
  list(APPEND flags "-Wextra" "-Wpedantic")
endif()

check_ipo_supported(RESULT can_use_ipo)
if(can_use_ipo)
  list(APPEND feature_tokens "ipo")
endif()

configure_file (
    "${PROJECT_SOURCE_DIR}/cmake/version.h.in"
    "${PROJECT_BINARY_DIR}/cmake/version.h"
)

##########
# Finish #
##########

list(JOIN feature_tokens " " feature_string)
message(STATUS "Built with these features:")
message(STATUS "${feature_string}")

message(STATUS "CMakeLists: top level done")