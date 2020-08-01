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
  ~ThreadObject();
  ThreadObject(const ThreadObject& other) = delete;
  ThreadObject(ThreadObject&&) = delete;
  ThreadObject& operator=(const ThreadObject& other) = delete;
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

  std::unique_ptr<std::thread> _thread_ = nullptr;
  mutable std::mutex _thread_mutex_;
  std::string _name_;
  std::atomic_bool _end_thread_ = false;
  std::queue<std::function<void()>> _queued_jobs_;
  mutable std::mutex _queue_mutex_;
};

}  // namespace ThreadLib