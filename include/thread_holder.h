#pragma once

#include <memory>
#include "thread_object.h"

namespace ThreadLib {

class ThreadHolder {
 public:
  ThreadHolder();
  ~ThreadHolder();

 private:
  std::shared_ptr<ThreadObject> __thread__;
};

}  // namespace ThreadLib