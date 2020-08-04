#pragma once

#include <cassert>
#include <future>
#include <memory>
#include "thread_object.h"

namespace ThreadLib {

class ThreadHolder {
 public:
  ThreadHolder(std::string name = "");
  ThreadHolder(const ThreadHolder& other) = default;
  ThreadHolder& operator=(const ThreadHolder& other) = default;
  ThreadHolder(ThreadHolder&&) = delete;
  ThreadHolder& operator=(ThreadHolder&&) = delete;
  ~ThreadHolder() = default;

  void asyncCall(const std::function<void(void)>& function) noexcept;

  template <class Retval>
  Retval syncCall(const std::function<Retval(void)>& function) noexcept {
    assert(_thread_);
    if (!_thread_->isRunning()) {
      _thread_->startThread();
    }

    std::promise<Retval> retval;

    _thread_->addCallback(
        [&retval, function]() { retval.set_value(function()); });

    auto future = retval.get_future();
    future.wait();
    return future.get();
  }

 private:
  std::shared_ptr<ThreadObject> _thread_;
};

}  // namespace ThreadLib