#include "thread_object.h"
#include <optional>

namespace ThreadLib {

ThreadObject::ThreadObject(const std::string& thread_name)
    : __name__(thread_name),
      __thread_mutex__(std::make_shared<std::mutex>()),
      __queued_jobs__(std::make_shared<std::queue<std::function<void()>>>()) {}

ThreadObject::ThreadObject(const ThreadObject& other) {}

ThreadObject& ThreadObject::operator=(const ThreadObject& other) {}

void ThreadObject::startThread() noexcept {
  std::lock_guard<std::mutex> lock(*__thread_mutex__);
  if (!__thread__) {
    __end_thread__ = false;
    __thread__ = std::make_shared<std::thread>(&ThreadObject::run, this);
  }
}

void ThreadObject::stopThread() noexcept {
  std::lock_guard<std::mutex> lock(*__thread_mutex__);
  __end_thread__ = true;
}

void ThreadObject::join() noexcept { return __thread__->join(); }
bool ThreadObject::joinable() const noexcept { return __thread__->joinable(); }

void ThreadObject::run() {
  while (!__end_thread__) {
    // execute all jobs
    for (auto job = nextJob(); job.has_value(); job = nextJob()) {
      job.value()();
    }
  }
}

void ThreadObject::addCallback(std::function<void()> callback) noexcept {
  std::lock_guard<std::mutex> lock(*__queue_mutex__);
  __queued_jobs__->push(callback);
}

std::optional<std::function<void()>> ThreadObject::nextJob() noexcept {
  std::lock_guard<std::mutex> lock(*__queue_mutex__);
  auto retval = __queued_jobs__->front();
  __queued_jobs__->pop();
  return retval;
}

}  // namespace ThreadLib