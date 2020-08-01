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
  explicit ThreadObject(std::string thread_name = "");
  ThreadObject(const ThreadObject& other) = default;
  ThreadObject(ThreadObject&&) = delete;
  ThreadObject& operator=(const ThreadObject& other) = default;
  ThreadObject& operator=(ThreadObject&&) = delete;

  void startThread() noexcept;
  void stopThread() noexcept;
  void addCallback(const std::function<void()>& callback) noexcept;

  void join() noexcept;
  bool joinable() const noexcept;

  bool isRunning() const noexcept;

  std::thread::id getId() const noexcept;

 private:
  virtual void run();
  std::optional<std::function<void()>> nextJob() noexcept;

  std::shared_ptr<std::thread> _thread_ = nullptr;
  mutable std::shared_ptr<std::mutex> _thread_mutex_;
  std::string _name_;
  std::shared_ptr<std::atomic_bool> _end_thread_ = nullptr;
  std::shared_ptr<std::queue<std::function<void()>>> _queued_jobs_;
  mutable std::shared_ptr<std::mutex> _queue_mutex_;
};

}  // namespace ThreadLib