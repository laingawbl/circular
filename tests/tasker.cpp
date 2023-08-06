
#include <catch2/catch_all.hpp>
#include <circular/tasker.hpp>
#include <taskflow/taskflow.hpp>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

TEST_CASE("Tasker executes a simple task", "[tasker]") {
  bool executed = false;

  auto fu = circular::Tasker::Get().Submit([&]() { executed = true; });
  fu.wait();

  REQUIRE(executed == true);
}

TEST_CASE("Tasker executes a tf::taskflow in order", "[tasker]") {
  std::string res = "";

  auto a_fn = [&res]() {
    std::this_thread::sleep_for(250ms);
    res.append("a");
  };
  auto b_fn = [&res]() { res.append("b"); };

  tf::Taskflow f;
  auto [a, b] = f.emplace(a_fn, b_fn);
  a.precede(b);
  auto fu = circular::Tasker::Get().Submit(std::move(f));
  fu.wait();

  REQUIRE(res == "ab");
}