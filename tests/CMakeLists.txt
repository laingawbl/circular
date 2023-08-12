# ##############################################################################
# Build unit tests #
# ##############################################################################

FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.3.2)
FetchContent_MakeAvailable(catch)

add_executable(tests test.cpp tasker.cpp config_map.cpp world.cpp)

set_target_properties(
  tests
  PROPERTIES CXX_STANDARD 20
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON
             LINKER_LANGUAGE CXX)

target_link_libraries(tests Catch2::Catch2WithMain)
target_link_libraries(tests libcircular)

enable_testing()

add_test(NAME catch_test COMMAND $<TARGET_FILE:tests> --success)

add_test(
  NAME integration_tests
  COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/integration_test.sh
          $<TARGET_FILE:tests>)
