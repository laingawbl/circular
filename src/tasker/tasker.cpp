#include "circular/tasker.hpp"

#include <taskflow/taskflow.hpp>

using namespace circular;

Tasker &circular::Tasker::Get() {
  if (nullptr == _instance) {
    _instance = new Tasker;
  }
  return *_instance;
}

TaskFuture circular::Tasker::Submit(std::function<void()> task) {
    tf::Taskflow f;
    auto t = f.emplace(task);
    return _ex.run(f);
}
