//
// Created by Tobias Fuchs on 08.08.20.
//

#pragma once

#include <thread_holder.h>
#include <chrono>

class Consumer : private ThreadLib::ThreadHolder {
 public:
  explicit Consumer(std::chrono::milliseconds timeout);
  const std::chrono::milliseconds _timeout;
  async(collect);

 private:
  void collect(int number);
};
