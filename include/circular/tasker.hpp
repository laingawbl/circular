#pragma once

#include <functional>
#include <taskflow/taskflow.hpp>

namespace circular {
// Thin wrapper around a tf::Future<void>
class Future {
public:
  /**
  @brief default constructor
  */
  Future() = default;

  /**
  @brief disabled copy constructor
  */
  Future(const Future &) = delete;

  /**
  @brief default move constructor
  */
  Future(Future &&) = default;

  /**
  @brief disabled copy assignment
  */
  Future &operator=(const Future &) = delete;

  /**
  @brief default move assignment
  */
  Future &operator=(Future &&) = default;

  /**
   * @brief move constructor from taskflow tf::Future
   */
  Future(tf::Future<void> &&f) : _f{std::move(f)} {}

  void wait() const { _f.wait(); }
  bool valid() const noexcept { return _f.valid(); }
  bool cancel() { return _f.cancel(); }

private:
  tf::Future<void> _f;
};

/**
 * @brief Tasker is a simple tasking facility that may or may not use taskflow.
 *
 * The intent of Tasker is that it can maybe be toggled in future, by creating
 * an abstract Tasker interface and implementing two classes: one using
 * Taskflow, and the other just executing tasks synchronously for e.g.
 * single-threaded apps
 */
class Tasker {
public:
  static Tasker &Get();
  Tasker(const Tasker &) = delete;
  Tasker &operator=(const Tasker &) = delete;

  Future Submit(std::function<void()> task);

  // Escape hatch to allow more complex tasks via TF
  Future Submit(tf::Taskflow &&t) { return _ex.run(std::move(t)); }

  size_t TaskCount() const { return _ex.num_taskflows(); }

private:
  Tasker() = default;
  ~Tasker() = default;

  static Tasker *_instance;
  tf::Executor _ex;
};
} // namespace circular