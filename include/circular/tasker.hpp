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
  //auto operator=(TaskFuture &&) = default;

  void wait() const { _f.wait(); }
  bool valid() const noexcept { return _f.valid(); }

private:
  tf::Future<void> _f;
};

class Tasker {
public:
  static Tasker &Get();
  TaskFuture Submit(std::function<void()> task);

private:
  Tasker() = default;
  ~Tasker() = default;

  static Tasker *_instance;
  tf::Executor _ex;
};
} // namespace circular