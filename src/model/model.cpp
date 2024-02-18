#include "circular/model.hpp"

#include <iostream>

using namespace circular;

circular::Model::Model() {
  model_thd_ = std::jthread(
      [&, stoken = model_thd_ssource_.get_token()]() { thdWorker(stoken); });
}

void circular::Model::TearDown() { model_thd_ssource_.request_stop(); }

void circular::Model::SignalOneTick() {
  {
    std::lock_guard{input_mtx_};
    tick_signalled_ = true;
  }
  tick_cv_.notify_all();
}

void circular::Model::AwaitWorkingOrReady() const {
  std::unique_lock lk{progress_mtx_};
  auto st = model_thd_.get_stop_token();
  progress_cv_.wait(lk, st, [this]() { return is_working_ || is_tick_ready_; });
}

void circular::Model::AwaitReady(bool p_reset_ready) {
  std::unique_lock lk{progress_mtx_};
  auto st = model_thd_.get_stop_token();
  progress_cv_.wait(lk, st, [this]() { return is_tick_ready_; });
  if (p_reset_ready) {
    is_tick_ready_ = false;
  }
}

void circular::Model::SetWaitForSignal(bool p_should_wait) {
  {
    std::lock_guard lk{input_mtx_};
    wait_for_signal_ = p_should_wait;
  }
  tick_cv_.notify_all();
}

void circular::Model::SetPaused(bool p_is_paused) {
  {
    std::lock_guard lk{input_mtx_};
    is_paused_ = p_is_paused;
  }
  tick_cv_.notify_all();
}

void circular::Model::awaitCanTick(const std::stop_token &st) {
  std::unique_lock lk{input_mtx_};

  tick_cv_.wait(lk, st, [this]() {
    // unsignalled mode
    if (!wait_for_signal_) {
      return !is_paused_;
    }

    // signalled mode
    if (!is_paused_ && tick_signalled_) {
      tick_signalled_ = false;
      return true;
    }
    return false;
  });
}

void circular::Model::enterTickUpdate() {
  {
    std::scoped_lock lk{progress_mtx_};
    is_working_ = true;
  }
  progress_cv_.notify_all();
}

void circular::Model::concludeTickUpdate() {
  // exit working section
  {
    std::scoped_lock lk{progress_mtx_};
    is_working_ = false;
    is_tick_ready_ = true;
  }
  progress_cv_.notify_all();
}

void circular::Model::thdWorker(const std::stop_token &st) {
  while (!st.stop_requested()) {
    awaitCanTick(st);
    if (st.stop_requested()) {
      return;
    }

    enterTickUpdate();

    // do work (TODO lol)
    {
      std::scoped_lock lk{output_mtx_};

      ++tick_;

      std::cout << "hullo! my tick is " << tick_ << "\n";
    }

    concludeTickUpdate();
  }

  std::cout << "thdWorker: return\n";
}
