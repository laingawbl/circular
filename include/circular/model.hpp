#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>

namespace circular {
class Model {
public:
  Model();

  ~Model() { TearDown(); }

  void TearDown();

  // Signal the model thread that execution can continue.
  void SignalOneTick();

  // Block till (is_working_ || is_tick_ready_).
  void AwaitWorkingOrReady() const;

  void AwaitReady(bool p_reset_ready);

  void SetWaitForSignal(bool p_should_wait);
  void SetPaused(bool p_is_paused);

  bool waitForSignal() const { return wait_for_signal_; }
  bool isWorking() const { return is_working_; }
  bool isTickReady() const { return is_tick_ready_; }
  bool isPaused() const { return is_paused_; }
  int tick() const { return tick_; }

private:
  void thdWorker(const std::stop_token &st);
  void awaitCanTick(const std::stop_token &st);
  void enterTickUpdate();
  void concludeTickUpdate();

  // whether to wait for tick_signalled_ before starting a tick update.
  bool wait_for_signal_ = true;

  // signals that a tick should proceed.
  bool tick_signalled_ = false;

  bool is_paused_ = true;
  bool is_working_ = false;
  bool is_tick_ready_ = false;

  // the model-wide tick is always at or leading the component systems' ticks.
  int tick_ = 0;

  std::jthread model_thd_;
  std::stop_source model_thd_ssource_;

  // notify this when tick_signalled_ or is_paused_ change.
  mutable std::condition_variable_any tick_cv_;

  // notify this when is_working_ or is_tick_ready_ changes.
  mutable std::condition_variable_any progress_cv_;

  mutable std::mutex input_mtx_;
  mutable std::mutex progress_mtx_;
  mutable std::mutex output_mtx_;
};
} // namespace circular