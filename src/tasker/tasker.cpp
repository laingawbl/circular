#include "circular/tasker.hpp"

#include <taskflow/taskflow.hpp>

using namespace circular;

Tasker *Tasker::_instance = nullptr;

Tasker &circular::Tasker::Get() {
  if (nullptr == _instance) {
    _instance = new Tasker;
  }
  return *_instance;
}

Future circular::Tasker::Submit(std::function<void()> task) {
  tf::Taskflow f;
  auto t = f.emplace(task);
  return _ex.run(std::move(f));
}
