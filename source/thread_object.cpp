#include "thread_object.h"
#include <optional>
#include <utility>

namespace ThreadLib {

ThreadObject::ThreadObject(std::string thread_name)
    : _name_(std::move(thread_name)),
      _thread_mutex_(std::make_shared<std::mutex>()),
      _queued_jobs_(std::make_shared<std::queue<std::function<void()>>>()),
      _queue_mutex_(std::make_shared<std::mutex>()),
      _end_thread_(std::make_shared<std::atomic_bool>(false)) {}

void ThreadObject::startThread() noexcept {
  if (!_thread_mutex_) {
    return;
  }

  std::lock_guard<std::mutex> lock(*_thread_mutex_);
  if (!_thread_) {
    *_end_thread_ = false;
    _thread_ = std::make_shared<std::thread>(&ThreadObject::run, this);
  }
}

void ThreadObject::stopThread() noexcept {
  if (!_thread_mutex_) {
    return;
  }
  std::lock_guard<std::mutex> lock(*_thread_mutex_);
  *_end_thread_ = true;
}

void ThreadObject::join() noexcept {
  if (!joinable()) {
    return;
  }
  std::lock_guard<std::mutex> lock(*_thread_mutex_);
  return _thread_->join();
}
bool ThreadObject::joinable() const noexcept {
  if (!_thread_mutex_) {
    return false;
  }
  std::lock_guard<std::mutex> lock(*_thread_mutex_);
  return (_thread_ != nullptr) && _thread_->joinable();
}

bool ThreadObject::isRunning() const noexcept { return joinable(); }

void ThreadObject::run() {
  while (!*_end_thread_) {
    // execute all jobs
    for (auto job = nextJob(); job.has_value(); job = nextJob()) {
      job.value()();
    }
  }
}

void ThreadObject::addCallback(const std::function<void()>& callback) noexcept {
  if (!_queue_mutex_) {
    return;
  }
  std::lock_guard<std::mutex> lock(*_queue_mutex_);
  _queued_jobs_->push(callback);
}

std::optional<std::function<void()>> ThreadObject::nextJob() noexcept {
  if (!_queue_mutex_) {
    return {};
  }
  std::lock_guard<std::mutex> lock(*_queue_mutex_);
  if (_queued_jobs_->empty()) {
    return std::optional<std::function<void()>>();
  }
  auto retval = _queued_jobs_->front();
  _queued_jobs_->pop();
  return retval;
}

std::thread::id ThreadObject::getId() const noexcept {
  if (_thread_ != nullptr) {
    return _thread_->get_id();
  }
  return {};
}

}  // namespace ThreadLib