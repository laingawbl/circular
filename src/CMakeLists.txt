#####################
# Build libcircular #
#####################

set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/circular/lib.hpp")

if(NOT DEFINED SOURCES_LIST)
  message(FATAL_ERROR "No sources are defined. Check SourceLists.cmake.")
endif()

add_library(libcircular
  STATIC
    ${SOURCES_LIST}
    ${HEADER_LIST}
  )

if(can_use_ipo)
  set_target_properties(libcircular PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set_target_properties(libcircular
  PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX
    POSITION_INDEPENDENT_CODE 1
    OUTPUT_NAME "circular"
  )
target_include_directories(libcircular
  PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
  )
target_compile_options(libcircular
  PRIVATE
    ${flags}
  )
target_compile_features(libcircular
  PUBLIC
  cxx_std_20
)