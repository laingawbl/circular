# ##############################################################################
# Build libcircular #
# ##############################################################################

# these are the PUBLIC headers only, not the ones in src/
set(HEADER_LIST
    "${PROJECT_SOURCE_DIR}/include/circular/config_map.hpp"
    "${PROJECT_SOURCE_DIR}/include/circular/lib.hpp"
    "${PROJECT_SOURCE_DIR}/include/circular/tasker.hpp")

if(NOT DEFINED SOURCES_LIST)
  message(FATAL_ERROR "No sources are defined. Check SourceLists.cmake.")
endif()

FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
  GIT_TAG v3.3.0)
FetchContent_MakeAvailable(tomlplusplus)

add_library(libcircular STATIC ${SOURCES_LIST} ${HEADER_LIST})

if(can_use_ipo)
  set_target_properties(libcircular PROPERTIES INTERPROCEDURAL_OPTIMIZATION
                                               TRUE)
endif()

set_target_properties(
  libcircular
  PROPERTIES CXX_STANDARD 20
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON
             LINKER_LANGUAGE CXX
             POSITION_INDEPENDENT_CODE 1
             OUTPUT_NAME "circular")
target_include_directories(libcircular PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(libcircular
                           PRIVATE "${tomlplusplus_SOURCE_DIR}/include")
target_compile_options(libcircular PRIVATE ${flags})
target_compile_features(libcircular PUBLIC cxx_std_20)

target_link_libraries(libcircular tomlplusplus::tomlplusplus)
target_link_libraries(libcircular Taskflow)

# trust ${CMAKE_INSTALL_LIBDIR} will know where to put it
install(TARGETS libcircular LIBRARY)
