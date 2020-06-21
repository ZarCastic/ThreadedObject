#pragma once

#include <chrono>
#include <functional>
#include <thread>

namespace test_util {

bool waitFor(std::function<bool()> condition,
             std::chrono::milliseconds timeout) {
  using namespace std::chrono_literals;
  while (!condition() && timeout > 0ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    timeout -= 100ms;
  }

  return condition();
}

}  // namespace test_util