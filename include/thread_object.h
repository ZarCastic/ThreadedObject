#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <thread>

namespace ThreadLib {

class ThreadObject {
 public:
  ThreadObject(const std::string& thread_name = "");
  ThreadObject(const ThreadObject& other);
  ThreadObject(ThreadObject&&) = delete;
  ThreadObject& operator=(const ThreadObject& other);
  ThreadObject& operator=(ThreadObject&&) = delete;

  virtual void addCallback(std::function<void()> callback) noexcept;
  void startThread() noexcept;
  void stopThread() noexcept;

  void join() noexcept;
  bool joinable() const noexcept;

 private:
  virtual void run();
  std::optional<std::function<void()>> nextJob() noexcept;

  std::shared_ptr<std::thread> __thread__ = nullptr;
  mutable std::mutex __thread_mutex__;
  const std::string __name__;
  std::atomic_bool __end_thread__ = false;
  std::queue<std::function<void()>> __queued_jobs__;
  mutable std::mutex __queue_mutex__;
};

}  // namespace ThreadLib