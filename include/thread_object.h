#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace ThreadLib {

class ThreadObject {
  ThreadObject(const std::string& thread_name = "");
  ThreadObject(const ThreadObject& other);
  ThreadObject(ThreadObject&&) = delete;
  ThreadObject& operator=(const ThreadObject& other);
  ThreadObject& operator=(ThreadObject&&) = delete;

 private:
  std::shared_ptr<std::thread> __thread__;
  std::shared_ptr<std::mutex> __thread_mutex_;
};

}  // namespace ThreadLib