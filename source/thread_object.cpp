#include "thread_object.h"
#include <iostream>
#include <optional>

namespace ThreadLib {

ThreadObject::ThreadObject(const std::string& thread_name)
    : __name__(thread_name),
      __thread_mutex__(std::make_shared<std::mutex>()),
      __queued_jobs__(std::make_shared<std::queue<std::function<void()>>>()),
      __queue_mutex__(std::make_shared<std::mutex>()) {}

ThreadObject::ThreadObject(const ThreadObject& other)
    : __thread__(other.__thread__),
      __name__(other.__name__),
      __thread_mutex__(other.__thread_mutex__),
      __queued_jobs__(other.__queued_jobs__),
      __queue_mutex__(other.__queue_mutex__) {}

ThreadObject& ThreadObject::operator=(const ThreadObject& other) {
  __thread__ = other.__thread__;
  __name__ = other.__name__;
  __thread_mutex__ = other.__thread_mutex__;
  __queued_jobs__ = other.__queued_jobs__;
  __queue_mutex__ = other.__queue_mutex__;
  return *this;
}

void ThreadObject::startThread() noexcept {
  if (!__thread_mutex__) {
    return;
  }

  std::lock_guard<std::mutex> lock(*__thread_mutex__);
  if (!__thread__) {
    __end_thread__ = false;
    __thread__ = std::make_shared<std::thread>(&ThreadObject::run, this);
  }
}

void ThreadObject::stopThread() noexcept {
  if (!__thread_mutex__) {
    return;
  }
  std::lock_guard<std::mutex> lock(*__thread_mutex__);
  __end_thread__ = true;
}

void ThreadObject::join() noexcept {
  if (!joinable()) {
    return;
  }
  std::lock_guard<std::mutex> lock(*__thread_mutex__);
  return __thread__->join();
}
bool ThreadObject::joinable() const noexcept {
  if (!__thread_mutex__) {
    return false;
  }
  std::lock_guard<std::mutex> lock(*__thread_mutex__);
  return (__thread__ != nullptr) && __thread__->joinable();
}

bool ThreadObject::isRunning() const noexcept { return joinable(); }

void ThreadObject::run() {
  while (!__end_thread__) {
    // execute all jobs
    for (auto job = nextJob(); job.has_value(); job = nextJob()) {
      job.value()();
    }
  }
}

void ThreadObject::addCallback(std::function<void()> callback) noexcept {
  if (!__queue_mutex__) {
    return;
  }
  std::lock_guard<std::mutex> lock(*__queue_mutex__);
  __queued_jobs__->push(callback);
}

std::optional<std::function<void()>> ThreadObject::nextJob() noexcept {
  if (!__queue_mutex__) {
    return {};
  }
  std::lock_guard<std::mutex> lock(*__queue_mutex__);
  if (__queued_jobs__->empty()) {
    return std::optional<std::function<void()>>();
  }
  auto retval = __queued_jobs__->front();
  __queued_jobs__->pop();
  return retval;
}

std::thread::id ThreadObject::getId() const noexcept {
  if (__thread__ != nullptr) {
    return __thread__->get_id();
  }
  return {};
}

}  // namespace ThreadLib