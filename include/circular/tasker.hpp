#pragma once

#include <functional>
#include <taskflow/taskflow.hpp>

namespace circular {
// Thin wrapper around a tf::Future<void>
class TaskFuture {
public:
  TaskFuture(const TaskFuture &) = delete;
  TaskFuture(TaskFuture &&) = default;
  TaskFuture(tf::Future<void> &&f) : _f{std::move(f)} {}

  auto operator=(const TaskFuture &) = delete;
  // auto operator=(TaskFuture &&) = default;

  void wait() const { _f.wait(); }
  bool valid() const noexcept { return _f.valid(); }

private:
  tf::Future<void> _f;
};

/**
 * @brief Tasker is a simple singleton interface to taskflow.
 *
 */
class Tasker {
public:
  static Tasker &Get();
  Tasker(const Tasker &) = delete;
  Tasker &operator=(const Tasker &) = delete;

  TaskFuture Submit(std::function<void()> task);

  // Escape hatch to allow more complex tasks via TF
  TaskFuture Submit(tf::Taskflow &&t) { return _ex.run(std::move(t)); }

private:
  Tasker() = default;
  ~Tasker() = default;

  static Tasker *_instance;
  tf::Executor _ex;
};
} // namespace circular