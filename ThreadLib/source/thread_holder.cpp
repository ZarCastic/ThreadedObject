#include "thread_holder.h"

namespace ThreadLib {

ThreadHolder::ThreadHolder(std::string name)
    : _thread_(std::make_shared<ThreadObject>(name)) {}

void ThreadHolder::asyncCall(
    const std::function<void(void)>& function) noexcept {
  assert(_thread_);
  if (!_thread_->isRunning()) {
    _thread_->startThread();
  }
  _thread_->addCallback([function]() { function(); });
}

std::thread::id ThreadHolder::getThreadId() noexcept {
  return std::this_thread::get_id();
}

}  // namespace ThreadLib