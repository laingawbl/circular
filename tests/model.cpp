#include <catch2/catch_all.hpp>
#include <circular/model.hpp>

#include <chrono>
#include <thread>

using namespace circular;
using namespace std::chrono;

TEST_CASE("Model: signalled mode: unpause, then signal tick", "[model]") {
  Model m{};

  REQUIRE(m.tick() == 0);

  m.SetPaused(false);

  REQUIRE(m.tick() == 0);

  m.SignalOneTick();
  m.AwaitReady(false);

  REQUIRE(m.isTickReady());
  REQUIRE(!m.isWorking());
  REQUIRE(m.tick() == 1);
}

TEST_CASE("Model: signalled mode: signal two ticks", "[model]") {
  Model m{};

  m.SetPaused(false);

  REQUIRE(m.tick() == 0);

  m.SignalOneTick();
  m.AwaitReady(true);

  REQUIRE(m.tick() == 1);

  m.SignalOneTick();
  m.AwaitReady(true);

  REQUIRE(m.tick() == 2);
}

TEST_CASE("Model: unignalled mode: unpause and pause again", "[model]") {
  Model m{};

  REQUIRE(m.tick() == 0);

  m.SetWaitForSignal(false);
  m.SetPaused(false);

  std::this_thread::sleep_for(microseconds(10));

  m.AwaitReady(false);
  m.SetPaused(true);

  auto tick_now = m.tick();
  REQUIRE(tick_now > 0);

  // now, check that the model hasn't advanced any more since pausing.
  std::this_thread::sleep_for(microseconds(10));

  REQUIRE(tick_now == m.tick());
}