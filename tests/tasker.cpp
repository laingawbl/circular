
#include <catch2/catch_all.hpp>
#include <circular/tasker.hpp>

#include <iostream>

TEST_CASE("Tasker executes a task", "[tasker]") {
  bool executed = false;

  auto fu = circular::Tasker::Get().Submit([&]() { executed = true; });
  fu.wait();

  REQUIRE(executed == true);
}
