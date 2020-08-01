#pragma once

#include <memory>
#include "thread_object.h"

namespace ThreadLib {

class ThreadHolder {
 public:
  ThreadHolder() = default;
  ThreadHolder(const ThreadHolder& other) = default;
  ThreadHolder& operator=(const ThreadHolder& other) = default;
  ThreadHolder(ThreadHolder&&) = delete;
  ThreadHolder& operator=(ThreadHolder&&) = delete;
  ~ThreadHolder() = default;

 private:
  std::shared_ptr<ThreadObject> _thread_;
};

}  // namespace ThreadLib