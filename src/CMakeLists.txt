#####################
# Build libcircular #
#####################

set(HEADER_LIST "${Circular_SOURCE_DIR}/include/circular/lib.hpp")

add_library(libcircular
  STATIC
    ${SOURCES_LIST}
    ${HEADER_LIST}
  )

set_target_properties(libcircular
  PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
    OUTPUT_NAME "message"
  )
target_compile_options(libcircular
  PRIVATE
    ${flags}
  )
target_compile_features(libcircular
  PUBLIC
  cxx_std_20
)